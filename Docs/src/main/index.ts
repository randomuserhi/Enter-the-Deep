declare namespace RHU {
    interface Modules {
        "main": void;
    }

    namespace Macro {
        interface TemplateMap
        {
            "appmount": appmount;
        }
    }
}

interface appmount extends HTMLDivElement
{
}
interface appmountConstructor extends RHU.Macro.Constructor<appmount>
{
    
}

RHU.module(new Error(), "main",
    { Macro: "rhu/macro", Style: "rhu/style", theme: "main/theme", navbar: "navbar" },
    function({ Macro, Style, theme, navbar })
    {
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

        const _appmount = function(this: appmount)
        {
            this.classList.toggle(`${theme}`, true);
        } as appmountConstructor;
        
        const appmount = Macro(_appmount, "appmount", //html
            `
            <rhu-macro rhu-type="${navbar}"></rhu-macro>
            <div class="${style.spacer}"></div>
            <div>
                Go deep,
                or go home.
            </div>
            `, {
                element: //html
                `<body class="${theme}"></body>`
            });
    }
);