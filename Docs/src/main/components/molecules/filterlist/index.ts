declare namespace RHU {
    interface Modules {
        "components/molecules/filterlist": "molecules/filterlist";
    }

    namespace Macro {
        interface TemplateMap {
            "molecules/filterlist": Molecules.Filterlist;
        }
    }
}

declare namespace Molecules {
    interface Filterlist extends HTMLDivElement {
        version: Atoms.Dropdown;
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
    const filterlist = Macro((() => {
        const filterlist = function(this: Molecules.Filterlist) {
            this.classList.add(`${style.wrapper}`);

            this.version.setOptions(docs.sort([...docs.versions.keys()], "desc").map(k => ({
                label: k,
                value: k,
            })));

        } as RHU.Macro.Constructor<Molecules.Filterlist>;

        return filterlist;
    })(), "molecules/filterlist", //html
        `
        <div class="${style.content}">
            <div>Version</div>
            <rhu-macro rhu-id="version" rhu-type="${dropdown}"></rhu-macro>
        </div>
        `, {
            element: //html
            `<div></div>`
        });

    return filterlist;
});