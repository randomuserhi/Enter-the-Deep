declare namespace RHU {
    interface Modules {
        "components/molecules/filterlist/style": {
            wrapper: Style.ClassName;
            content: Style.ClassName;
            path: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "components/molecules/filterlist/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            const wrapper = style.class`
            position: relative;
            width: 25%;
            min-width: 200px;
            flex-shrink: 0;
            `;

            const content = style.class`
            position: sticky;
            top: var(--Navbar_height);
            width: 100%;
            height: calc(100vh - var(--Navbar_height));
            background-color: #eee;
            `

            const path = style.class`
            display: flex;
            `;
            style`
            ${path} > span::after {
                content: "/";
                padding: 3px; 0;
            }
            `;
            
            return {
                wrapper,
                content,
                path,
            };
        });

        return style;
    }
);