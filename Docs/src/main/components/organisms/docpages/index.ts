declare namespace RHU {
    interface Modules {
        "components/organisms/docpages": "organisms/docpages";
    }

    namespace Macro {
        interface TemplateMap {
            "organisms/docpages": Organisms.Docpages;
        }
    }
}

declare namespace Organisms {
    interface Docpages extends HTMLDivElement {
        content: HTMLDivElement;
    }
}

RHU.module(new Error(), "components/organisms/docpages", { 
    Macro: "rhu/macro", style: "components/organsisms/docpages/style",
    rhuDocuscript: "docuscript"
}, function({ 
    Macro, style,
    rhuDocuscript,
}) {
    const docpages = Macro((() => {
        const docpages = function(this: Organisms.Docpages) {
            /* Example page */
            let page = docuscript("test", ({ h, block, br, img }) => {
                h(1, "This is a heading");
                img("https://avatars.githubusercontent.com/u/40913834?s=40&v=4");
                block(
                    "This is a paragraph",
                    "multiline?",
                    br(),
                    `no idea how this
                    will
                    render so...`,
                    block(
                        "nested blocks"
                    )
                );
            }, rhuDocuscript);
            this.content.append(docuscript.render(page));
        } as RHU.Macro.Constructor<Organisms.Docpages>;

        return docpages;
    })(), "organisms/docpages", //html
        `
        <div>sidebar?</div>
        <div rhu-id="content"></div>
        `, {
            element: //html
            `<div class="${style.wrapper}"></div>`
        });

    return docpages;
});