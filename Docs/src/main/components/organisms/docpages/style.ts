declare namespace RHU {
    interface Modules {
        "components/organsisms/docpages/style": {
            wrapper: Style.ClassName;
            margin: Style.ClassName;
            sidebar: Style.ClassName;
            content: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "components/organsisms/docpages/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            const wrapper = style.class`
            height: 100%;
            padding: 0 70px;
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${wrapper} {
                    padding: 7px 30px;
                }
            }
            `;

            const margin = style.class`
            height: 100%;
            width: 100%;
            max-width: 1200px;

            margin: 0 auto;

            display: flex;
            `;

            const sidebar = style.class`
            width: var(--Sidebar_width);
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${sidebar} {
                    display: none;
                }
            }
            `;

            const content = style.class`
                padding: 0 15px;
            `;

            return {
                wrapper,
                margin,
                sidebar,
                content
            };
        });

        return style;
    }
);