declare namespace RHU {
    interface Modules {
        "components/molecules/filterlist/style": {
            wrapper: Style.ClassName;
            content: Style.ClassName;
            path: Style.ClassName;
            filteritem: Style.ClassName;
            dropdown: Style.ClassName;
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
            overflow-y: auto;
            `

            const path = style.class`
            display: flex;
            `;
            style`
            ${path} > li::after {
                content: "/";
                padding: 3px; 0;
            }
            `;
            
            const filteritem = style.class`
            cursor: pointer;
            -webkit-user-select: none;
            user-select: none;
            `;

            const dropdown = style.class`
            `;
            style`
            ${dropdown}::before {
                font-family: docons;
                content: "Ｔ";
            }
            `;

            return {
                wrapper,
                content,
                path,
                filteritem,
                dropdown,
            };
        });

        return style;
    }
);