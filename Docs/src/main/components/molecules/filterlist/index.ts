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
    }
}

RHU.module(new Error(), "components/molecules/filterlist", { 
    Macro: "rhu/macro", style: "components/molecules/filterlist/style",
}, function({ 
    Macro, style,
}) {
    const filterlist = Macro((() => {
        const filterlist = function(this: Molecules.Filterlist) {
            this.classList.add(`${style.wrapper}`);
        } as RHU.Macro.Constructor<Organisms.Docpages>;

        return filterlist;
    })(), "molecules/filterlist", //html
        `
        <div class="${style.content}"></div>
        `, {
            element: //html
            `<div></div>`
        });

    return filterlist;
});