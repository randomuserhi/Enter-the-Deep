// TODO(randomuserhi): Macros "headeritem" and "filteritem" are very similar, the only difference are their styling
//                     - I should combine them into 1 Macro for cleaner code.

declare namespace RHU {
    interface Modules {
        "components/organisms/docpages": "organisms/docpages";
    }

    namespace Macro {
        interface TemplateMap {
            "organisms/docpages": Organisms.Docpages;
            "atoms/headeritem": Atoms.Headeritem;
        }
    }
}

declare namespace Organisms {
    interface Docpages extends HTMLDivElement {
        view(version: string, page: string): void;
        render(page: RHUDocuscript.Page): void;
        setPath(path?: string): void;

        content: HTMLDivElement;
        filterlist: Molecules.Filterlist;
        headerlist: HTMLDivElement;
        path: HTMLDivElement;
        
        currentPath: string;
        currentVersion: string;
    }
}

declare namespace Atoms {
    interface Headeritem extends HTMLDivElement {
        set(label: string): void;
        add(item: Node): void;

        target: Node;

        label: HTMLDivElement;
        list: HTMLDivElement;
    }
}

RHU.module(new Error(), "components/organisms/docpages", { 
    Macro: "rhu/macro", style: "components/organsisms/docpages/style",
    filterlist: "components/molecules/filterlist",
    rhuDocuscript: "docuscript", docs: "docs", indices: "docs/indices",
}, function({ 
    Macro, style,
    filterlist,
    rhuDocuscript,
    docs, indices,
}) {
    const DOCUSCRIPT_ROOT = indices.DOCUSCRIPT_ROOT;

    const path = {
        join: function (...paths: string[]) {
            const separator = "/";
            paths = paths.map((part, index) => {
                if (index)
                    part = part.replace(new RegExp("^" + separator), "");
                if (index !== paths.length - 1)
                    part = part.replace(new RegExp(separator + "$"), "");
                return part;
            });
            return paths.join(separator);
        },
        isAbsolute: function (path: string) {
            return /^([a-z]+:)?[\\/]/i.test(path);
        }
    };

    const LoadingPage = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "Page is loading.");
    }, rhuDocuscript);

    const FailedLoadingPage = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "Page failed to load.");
    }, rhuDocuscript);

    const PageNotFound = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "Page not found.");
    }, rhuDocuscript);

    const VersionNotFound = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "Version not found.");
    }, rhuDocuscript);

    const DirectoryPage = (directory: Page) => {
        return docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({

        }) => {

        }, rhuDocuscript);
    }

    const headeritem = Macro((() => {
        const headeritem = function(this: Atoms.Headeritem) {
            this.classList.add(`${style.headeritem}`);

            this.label.addEventListener("click", (e) => {
                this.dispatchEvent(RHU.CustomEvent("view", { target: this.target }));
                e.preventDefault(); // stop redirect
            });
        } as RHU.Macro.Constructor<Atoms.Headeritem>;

        headeritem.prototype.set = function(label: string) {
            this.label.innerHTML = label;
        };

        headeritem.prototype.add = function(item: HTMLElement) {
            this.list.append(item);
        };

        return headeritem;
    })(), "atoms/headeritem", //html
        `
            <a href="file:///E:/Git/Enter-the-Deep/Docs/build/main/main.html?10" rhu-id="label"></a>
            <ol rhu-id="list">
            </ol>
        `, {
            element: //html
            `<ol></ol>`
        });

    const docpages = Macro((() => {
        const docpages = function(this: Organisms.Docpages) {

            this.filterlist.version.addEventListener("change", () => {
                this.currentVersion = this.filterlist.version.value;
                this.view(this.currentVersion, this.currentPath);
            });
            this.filterlist.addEventListener("view", (e) => {
                const page = e.detail.target as Page;
                this.view(this.currentVersion, page.fullPath());
            });

            this.currentPath = "home";
            this.currentVersion = this.filterlist.version.value;
            this.view(this.currentVersion, this.currentPath);

        } as RHU.Macro.Constructor<Organisms.Docpages>;

        docpages.prototype.render = function(page) {
            // TODO(randomuserhi): generate a label -> node map so that after page render we can seek to a header node via its label
            //                     - used when loading URL query params for a page if a link to a specific title is provided

            const frag = new DocumentFragment();
            const stack: Atoms.Headeritem[] = [];
            const depths: number[] = [];
            this.content.replaceChildren(docuscript.render<RHUDocuscript.Language, RHUDocuscript.FuncMap>(page, { 
                post: (node, dom) => {
                    if (node.__type__ === "h") {
                        const h = node as RHUDocuscript.Node<"h">;
                        
                        let depth = depths.length === 0 ? Infinity : depths[depths.length - 1];
                        while (h.heading <= depth && depths.length > 0) {
                            depths.pop();
                            stack.pop();
                            depth = depths[depths.length - 1];
                        }

                        const parent = stack.length === 0 ? undefined : stack[stack.length - 1];
                        
                        const item = document.createMacro(headeritem);
                        item.addEventListener("view", (e) => {
                            const node = e.detail.target as HTMLElement;
                            node.scrollIntoView(true);
                        });
                        item.target = dom;
                        item.set(h.label);
                        
                        stack.push(item);
                        depths.push(h.heading);
                        
                        if (parent) {
                            parent.add(item);
                        } else {
                            frag.append(item);
                        }
                    }
                }
            }));
            this.headerlist.replaceChildren(frag);
        }

        docpages.prototype.view = function(versionStr, pageStr) {
            this.currentVersion = versionStr;
            this.currentPath = pageStr;
            const version = docs.get(this.currentVersion);
            if (RHU.exists(version)) {
                const directory = version.get(this.currentPath);
                if (RHU.exists(directory)) {
                    if (RHU.exists(directory.page)) {
                        this.setPath(this.currentPath);
                        if (RHU.exists(directory.page.cache)) {
                            this.render(directory.page.cache);
                        } else {
                            this.render(LoadingPage);
                            if (!directory.page.loading) {
                                const script = document.createElement("script");
                                script.onload = () => {
                                    this.render(directory.page!.cache!);
                                };
                                script.onerror = () => {
                                    this.render(FailedLoadingPage);
                                    directory!.page!.loading = false;
                                    script.replaceWith();
                                };
                                script.src = path.join(DOCUSCRIPT_ROOT, this.currentVersion, directory.page.path);
                                document.head.append(script);
                            }
                        }
                    } else {
                        this.render(DirectoryPage(directory));
                    }
                } else {
                    this.render(PageNotFound);
                }
            } else {
                this.render(VersionNotFound);
            }
        }

        docpages.prototype.setPath = function(path) {
            if (!path) {
                this.path.replaceChildren();
            } else {
                let frag = new DocumentFragment();
                let builtPath: string[] = [];
                for (const directory of docs.split(path)) {
                    const item = document.createElement("a");
                    item.href = "file:///E:/Git/Enter-the-Deep/Docs/build/main/main.html?10";
                    item.innerHTML = directory;
                    
                    builtPath.push(directory);
                    const p = [...builtPath].join("/");
                    item.addEventListener("click", (e) => {
                        this.view(this.currentVersion, p);
                        e.preventDefault();
                    });

                    const wrapper = document.createElement("li");
                    wrapper.append(item);
                    frag.append(wrapper);
                }
                this.path.replaceChildren(frag);
            }
        };

        return docpages;
    })(), "organisms/docpages", //html
        `
        <div class="${style.margin}">
            <rhu-macro rhu-id="filterlist" class="${style.sidebar}" rhu-type="${filterlist}"></rhu-macro>
            <div class="${style.page}">
                <div class="${style.content}">
                    <ol rhu-id="path" class="${style.path}">title?</ol>
                    <div rhu-id="content"></div>
                </div>
                <div class="${style.outline}">
                    <div class="${style.outline.content}">
                        In this article
                        <ol rhu-id="headerlist"></ol>
                    </div>
                </div>
            </div>
        </div>
        `, {
            element: //html
            `<div class="${style.wrapper}"></div>`
        });

    return docpages;
});