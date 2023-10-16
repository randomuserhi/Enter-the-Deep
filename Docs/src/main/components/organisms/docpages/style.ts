declare namespace RHU {
    interface Modules {
        "components/organsisms/docpages/style": {
            wrapper: Style.ClassName;
            margin: Style.ClassName;
            sidebar: Style.ClassName;
            page: Style.ClassName;
            content: Style.ClassName;
            outline: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "components/organsisms/docpages/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            const wrapper = style.class`
            padding: 0 70px;
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${wrapper} {
                    padding: 0px 7px;
                }
            }
            `;

            const margin = style.class`
            width: 100%;
            max-width: 1800px;

            margin: 0 auto;

            display: flex;
            `;

            const sidebar = style.class`
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${sidebar} {
                    display: none;
                }
            }
            `;

            const page = style.class`
            display: flex;
            width: 100%;
            `;

            const content = style.class`
            padding: 0 15px;
            flex: 1;
            `;

            const outline = style.class`
            flex: 0.5;
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${outline} {
                    display: none;
                }
            }
            `;

            return {
                wrapper,
                margin,
                sidebar,
                page,
                content,
                outline,
            };
        });

        return style;
    }
);