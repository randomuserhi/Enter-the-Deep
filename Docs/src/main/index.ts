declare namespace RHU {
    interface Modules {
        "main": void;
    }

    namespace Macro {
        interface TemplateMap {
            "App": App;
        }
    }
}

interface App extends HTMLDivElement {
    body: HTMLDivElement;
}

RHU.module(new Error(), "main", { 
    Macro: "rhu/macro", Style: "rhu/style", 
    theme: "main/theme", navbar: "components/organisms/navbar",
    rhuDocuscript: "docuscript"
}, function({ Macro, Style, theme, navbar, rhuDocuscript }) {
    const style = Style(({ style }) => {
        const spacer = style.class`
        position: relative;

        width: 100%;
        height: var(--Navbar_height);
        `;

        style/*css*/`
        :root {
            --font-family: "IBM Plex Sans";
            --font-size: 1rem;
        }

        body {
            font-family: var(--font-family);
            font-size: var(--font-size);
        }
        `

        return {
            spacer
        };
    });
    
    Macro((() => {
        const appmount = function(this: App) {
            this.classList.toggle(`${theme}`, true);   

            let page = docuscript("test", ({ h, block, br }) => {
                h(1, "This is a heading");
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

            this.body.append(docuscript.render(page));
        } as RHU.Macro.Constructor<App>;

        return appmount
    })(), "App", //html
        `
        <rhu-macro rhu-type="${navbar}"></rhu-macro>
        <div class="${style.spacer}"></div>
        <div rhu-id="body">
            Go deep,
            or go home.
        </div>
        `, {
            element: //html
            `<div class="${theme}"></div>`
        });
});