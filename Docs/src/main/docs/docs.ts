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

interface Docs {
    version: string;
    directories: Map<string, Directory>;
    get(path: string): Directory | undefined;
}

interface Directory {
    name: string;
    page?: RHUDocuscript.Page;
    subDirectories: Directory[];
}

RHU.module(new Error(), "docs", { 
}, function({}) {

    const versions = new Map<string, Docs>();

    return {
        versions,
        get(version) {
            return versions.get(version);
        },
        create(version) {
            // TODO(randomuserhi): convert to object constructor
            const docs: Docs = {
                version: version,
                directories: new Map(),
                get: function(path: string) {
                    return this.directories.get(path);
                }
            };
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