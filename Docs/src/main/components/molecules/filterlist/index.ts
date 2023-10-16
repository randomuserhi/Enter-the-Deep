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
    }
}

declare namespace Molecules {
    interface Filterlist extends HTMLDivElement {
        load(version: string): void;
        
        root?: string;

        version: Atoms.Dropdown;
        search: HTMLInputElement;
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
    //TODO(randomuserhi): convert to filterlist and have it recursive (use itself to make nested items)
    const filteritem = Macro((() => {
        const filteritem = function(this: Atoms.Filteritem) {

        } as RHU.Macro.Constructor<Atoms.Filteritem>;

        filteritem.prototype.set = function(page) {
            this.innerHTML = page.name;
        };

        return filteritem;
    })(), "atoms/filteritem", //html
        `
        `, {
            element: //html
            `<div></div>`
        });

    //TODO(randomuserhi): convert to wrapper
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
            for (const page of root.subDirectories.keys()) {
                const item = document.createMacro("atoms/filteritem");
                item.set(root.subDirectories.get(page)!);
                fragment.append(item);
            }
            this.list.replaceChildren(fragment);
        };

        return filterlist;
    })(), "molecules/filterlist", //html
        `
        <div class="${style.content}">
            <div>Version</div>
            <rhu-macro rhu-id="version" rhu-type="${dropdown}"></rhu-macro>
            <input rhu-id="search" type="text"/>
            <div></div>
            <div rhu-id="list"></div>
        </div>
        `, {
            element: //html
            `<div></div>`
        });

    return filterlist;
});