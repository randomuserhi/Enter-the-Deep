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

        content: HTMLDivElement;
        filterlist: Molecules.Filterlist;
        headerlist: HTMLDivElement;

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
    rhuDocuscript: "docuscript", docs: "docs",
}, function({ 
    Macro, style,
    filterlist,
    rhuDocuscript,
    docs,
}) {
    console.log(docs);
    
    const a = docs.create("0.0.1");
    a.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
    }, rhuDocuscript));
    a.set("some/nested/file", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "0.0.1");
        h(2, "some/nested/file");
    }, rhuDocuscript));
    a.set("some/nested", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
        h(2, "some/nested");
    }, rhuDocuscript));
    a.set("some/nested/cringe", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
        h(2, "some/nested/cringe");
    }, rhuDocuscript));
    a.set("some/nested_2", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
        h(2, "some/nested_2");
    }, rhuDocuscript));
    a.set("a/nested_2", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
        h(2, "a/nested_2");
    }, rhuDocuscript));

    const b = docs.create("0.0.2");
    b.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.2");
    }, rhuDocuscript));

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
            <ul rhu-id="list">
            </ul>
        `, {
            element: //html
            `<li></li>`
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
                        this.render(directory.page);
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

        return docpages;
    })(), "organisms/docpages", //html
        `
        <div class="${style.margin}">
            <rhu-macro rhu-id="filterlist" class="${style.sidebar}" rhu-type="${filterlist}"></rhu-macro>
            <div class="${style.page}">
                <div class="${style.content}">
                    <div>title?</div>
                    <div rhu-id="content"></div>
                </div>
                <div class="${style.outline}">
                    <div class="${style.outline.content}">
                        In this article
                        <ul rhu-id="headerlist"></ul>
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