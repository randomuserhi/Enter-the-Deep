declare namespace RHU {
    interface Modules {
        "docs": {
            sort(data: string[], opt?: "asc" | "desc"): string[];
            get(version: string): Docs | undefined;
            create(version: string): Docs;
            versions: Map<string, Docs>;
            split(path: string): string[];
        };
    }
}

interface Directory {
    get(path: string): Page | undefined;
    set(path: string, page?: RHUDocuscript.Page): void;
    fullPath(): string;
    sortedKeys(): string[];

    parent?: Directory;
    subDirectories: Map<string, Page>;
}

interface Docs extends Directory {
    version: string;   
}

interface Page extends Directory  {
    name: string;
    page?: RHUDocuscript.Page;
}

RHU.module(new Error(), "docs", { 
}, function({}) {

    const versions = new Map<string, Docs>();

    interface DirectoryConstructor {
        new(name: string, parent?: Directory): Page;
        prototype: Page;
    }

    const split = (path: string): string[] => {
        const paths = path.split(/[\/\\]/g);
        if (paths.length > 0 && paths[paths.length - 1].trim() === "") {
            return paths.slice(0, paths.length - 1);
        }
        return paths;
    };

    const Directory = function(this: Page, name: string, parent?: Directory) {
        this.name = name;
        this.parent = parent;
        this.subDirectories = new Map();
    } as unknown as DirectoryConstructor;
    Directory.prototype.get = function(path) {
        const paths = split(path);
        let current: Page | undefined = this;
        for (const p of paths) {
            if (!current) break;
            current = current.subDirectories.get(p);
        }
        return current;
    };
    Directory.prototype.set = function(path, page) {
        const paths = split(path);
        let current: Page = this;
        for (const p of paths) {
            if (!current.subDirectories.has(p)) {
                current.subDirectories.set(p, new Directory(p, current));
            }
            current = current.subDirectories.get(p)!;
        }
        current.page = page;
    };
    Directory.prototype.fullPath = function() {
        const path: string[] = [];
        for (let current: Directory | undefined = this; RHU.exists(current); current = current.parent) {
            if ((current as Page).name) {
                path.push((current as Page).name);
            }
        }
        return path.reverse().join("/");
    }
    Directory.prototype.sortedKeys = function() {
        return [...this.subDirectories.keys()].sort();
    }

    interface DocsConstructor {
        new(version: string): Docs;
        prototype: Docs;
    }

    const Docs = function(this: Docs, version: string) {
        this.version = version;
        this.subDirectories = new Map();
    } as unknown as DocsConstructor;
    RHU.inherit(Docs, Directory);

    return {
        versions,
        get(version) {
            return versions.get(version);
        },
        create(version) {
            // TODO(randomuserhi): convert to object constructor
            const docs: Docs = new Docs(version);
            versions.set(version, docs);
            return docs;
        },
        sort(data, opt) {
            function isNumber(v: any): v is number {
                return (+v).toString() === v;
            }
        
            var sort = {
                asc: function (a: { index: number, value: string[] }, b: { index: number, value: string[] }) {
                    var i = 0,
                        l = Math.min(a.value.length, b.value.length);
        
                    while (i < l && a.value[i] === b.value[i]) i++;
        
                    if (i === l) return a.value.length - b.value.length;
                    if (isNumber(a.value[i]) && isNumber(b.value[i])) return (a.value[i] as any) - (b.value[i] as any);
                    return a.value[i].localeCompare(b.value[i]);
                },
                desc: function (a: { index: number, value: string[] }, b: { index: number, value: string[] }) {
                    return sort.asc(b, a);
                }
            }
            var mapped = data.map((el, i) => {
                return {
                    index: i,
                    value: el.split('.')
                };
            });
        
            mapped.sort(sort[opt as keyof typeof sort] || sort.asc);
        
            return mapped.map(function (el) {
                return data[el.index];
            });
        },
        split,
    };
});