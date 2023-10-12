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
    filterlist: "components/molecules/filterlist",
    rhuDocuscript: "docuscript"
}, function({ 
    Macro, style,
    filterlist,
    rhuDocuscript,
}) {
    const docpages = Macro((() => {
        const docpages = function(this: Organisms.Docpages) {
            /* Example page */
            let page = docuscript(({ h, div, br, img }) => {
                h(1, "This is a heading");
                img("https://avatars.githubusercontent.com/u/40913834?s=40&v=4");

                for (let i = 0; i < 20; ++i) {
                    div(
                        "This is a paragraph",
                        "multiline?",
                        br(),
                        `no idea how this
                        will
                        render so...`,
                        div(
                            "nested blocks"
                        )
                    );
                }
            }, rhuDocuscript);
            this.content.append(docuscript.render(page));
        } as RHU.Macro.Constructor<Organisms.Docpages>;

        return docpages;
    })(), "organisms/docpages", //html
        `
        <div class="${style.margin}">
            <rhu-macro class="${style.sidebar}" rhu-type="${filterlist}"></rhu-macro>
            <div class="${style.content}">
                <div>title?</div>
                <div rhu-id="content"></div>
            </div>
        </div>
        `, {
            element: //html
            `<div class="${style.wrapper}"></div>`
        });

    return docpages;
});