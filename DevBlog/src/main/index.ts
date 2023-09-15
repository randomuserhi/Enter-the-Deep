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
}

RHU.module(new Error(), "main", { 
    Macro: "rhu/macro", Style: "rhu/style", 
    theme: "main/theme", navbar: "components/organisms/navbar" 
}, function({ Macro, Style, theme, navbar }) {
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
    
    const appmount = Macro((() => {
        const appmount = function(this: App) {
            this.classList.toggle(`${theme}`, true);   
        } as RHU.Macro.Constructor<App>;

        return appmount
    })(), "App", //html
        `
        <rhu-macro rhu-type="${navbar}" />
        <div class="${style.spacer}"></div>
        <div>
            Go deep,
            or go home.
        </div>
        `, {
            element: //html
            `<div class="${theme}"></div>`
        });
});