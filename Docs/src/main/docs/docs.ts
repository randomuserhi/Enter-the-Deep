declare namespace RHU {
    interface Modules {
        "docs": {
            sort(data: string[], opt?: "asc" | "desc"): string[];
            versions: Map<string, Docs>;
            get(version: string): Docs | undefined;
            create(version: string): Docs;
        };
    }
}

interface Directory {
    subDirectories: Map<string, Page>;
    get(path: string): Page | undefined;
    set(path: string, page?: RHUDocuscript.Page): void;
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
        new(name: string, page?: RHUDocuscript.Page): Page;
        prototype: Page;
    }

    const split = (path: string): string[] => {
        const paths = path.split(/[\/\\]/g);
        if (paths.length > 0 && paths[paths.length - 1].trim() === "") {
            return paths.slice(0, paths.length - 1);
        }
        return paths;
    };

    const Directory = function(this: Page, name: string, page?: RHUDocuscript.Page) {
        this.name = name;
        this.page = page;
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
                current.subDirectories.set(p, new Directory(p));
            }
            current = current.subDirectories.get(p)!;
        }
        current.page = page;
    };

    interface DocsConstructor {
        new(version: string): Docs;
        prototype: Docs;
    }

    const Docs = function(this: Docs, version: string) {
        this.version = version;
        this.subDirectories = new Map();
    } as unknown as DocsConstructor;
    Docs.prototype.get = function(path) {
        const paths = split(path);
        let current: Page | undefined;
        for (const p of paths) {
            let map = current ? current.subDirectories : this.subDirectories;
            current = map.get(p);
            if (!current) break;
        }
        return current;
    };
    Docs.prototype.set = function(path, page) {
        const paths = split(path);
        let current: Page | undefined;
        for (const p of paths) {
            let map = current ? current.subDirectories : this.subDirectories;
            if (!map.has(p)) {
                map.set(p, new Directory(p));
            }
            current = map.get(p)!;
        }
        if (!current) {
            throw new ReferenceError("Directory should not be undefined or null here.");
        }
        current.page = page;
    };

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
    };
});