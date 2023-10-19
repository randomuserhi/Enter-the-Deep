interface GlobalEventHandlersEventMap {
    "view": CustomEvent<{ page: Page }>;
}

declare namespace RHU {
    interface Modules {
        "components/molecules/filterlist": "molecules/filterlist";
    }

    namespace Macro {
        interface TemplateMap {
            "molecules/filterlist": Molecules.Filterlist;
            "atoms/filteritem": Atoms.Filteritem;
        }
    }
}

declare namespace Atoms {
    interface Filteritem extends HTMLDivElement {
        set(page: Page): void;
    
        page?: Page;
        label: HTMLDivElement;
        list: HTMLDivElement;
    }
}

declare namespace Molecules {
    interface Filterlist extends HTMLDivElement {
        load(version: string): void;
        setPath(path?: string): void;
        
        root?: string;

        version: Atoms.Dropdown;
        search: HTMLInputElement;
        path: HTMLDivElement;
        list: HTMLDivElement;
    }
}

RHU.module(new Error(), "components/molecules/filterlist", { 
    Macro: "rhu/macro", style: "components/molecules/filterlist/style",
    dropdown: "components/atoms/dropdown",
    docs: "docs",
}, function({ 
    Macro, style,
    dropdown,
    docs,
}) {
    const filteritem = Macro((() => {
        const filteritem = function(this: Atoms.Filteritem) {
            this.label.addEventListener("click", () => {
                this.dispatchEvent(RHU.CustomEvent("view", { page: this.page }));
            });
        } as RHU.Macro.Constructor<Atoms.Filteritem>;

        filteritem.prototype.set = function(page) {
            this.label.innerHTML = page.fullPath();

            this.page = page;

            const fragment = new DocumentFragment();
            for (const p of page.sortedKeys()) {
                const item = document.createMacro("atoms/filteritem");
                item.set(page.subDirectories.get(p)!);
                item.addEventListener("view", (e) => {
                    this.dispatchEvent(RHU.CustomEvent("view", e.detail));
                });
                fragment.append(item);
            }
            this.list.replaceChildren(fragment);
        };

        return filteritem;
    })(), "atoms/filteritem", //html
        `
            <div rhu-id="label"></div>
            <div rhu-id="list">
            </div>
        `, {
            element: //html
            `<div></div>`
        });

    const filterlist = Macro((() => {
        const filterlist = function(this: Molecules.Filterlist) {
            this.classList.add(`${style.wrapper}`);

            this.version.setOptions(docs.sort([...docs.versions.keys()], "desc").map(k => ({
                label: k,
                value: k,
            })));

            this.version.addEventListener("change", () => {
                this.load(this.version.value);
            });

            this.root = undefined;
            this.setPath(this.root);

            this.load(this.version.value);
        } as RHU.Macro.Constructor<Molecules.Filterlist>;

        filterlist.prototype.load = function(versionStr) {
            const version = docs.get(versionStr);
            if (!RHU.exists(version)) {
                this.list.replaceChildren();
                return;   
            }
            const fragment = new DocumentFragment();
            const root: Directory | undefined = this.root ? version.get(this.root) : version;
            if (!root) {
                // TODO(randomuserhi): Root not found error
                return;
            }
            for (const page of root.sortedKeys()) {
                const item = document.createMacro("atoms/filteritem");
                const view = root.subDirectories.get(page)!;
                item.addEventListener("view", (e) => {
                    this.dispatchEvent(RHU.CustomEvent("view", e.detail));
                });
                item.set(view);
                fragment.append(item);
            }
            this.list.replaceChildren(fragment);
        };

        filterlist.prototype.setPath = function(path) {
            if (!path) {
                this.path.replaceChildren();
                return;
            }
            let frag = new DocumentFragment();
            for (const directory of docs.split(path)) {
                const item = document.createElement("span");
                item.innerHTML = directory;
                frag.append(item);
            }
            this.path.replaceChildren(frag);
        };

        return filterlist;
    })(), "molecules/filterlist", //html
        `
        <div class="${style.content}">
            <div>Version</div>
            <rhu-macro rhu-id="version" rhu-type="${dropdown}"></rhu-macro>
            <input rhu-id="search" type="text"/>
            <div rhu-id="path" class="${style.path}"></div>
            <div rhu-id="list"></div>
        </div>
        `, {
            element: //html
            `<div></div>`
        });

    return filterlist;
});