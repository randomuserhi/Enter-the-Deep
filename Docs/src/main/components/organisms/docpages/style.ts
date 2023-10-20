declare namespace RHU {
    interface Modules {
        "components/organsisms/docpages/style": {
            wrapper: Style.ClassName;
            margin: Style.ClassName;
            sidebar: Style.ClassName;
            page: Style.ClassName;
            content: Style.ClassName;
            outline: Style.ClassName<{
                content: Style.ClassName;
            }>;
            headeritem: Style.ClassName;
            path: Style.ClassName;
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

            const outline = style.class<{
                wrapper: RHU.Style.ClassName;
                content: RHU.Style.ClassName;
            }>`
            position: relative;
            flex: 0.5;
            flex-shrink: 0;
            `;
            style/*css*/`
            @media screen and (max-width: 780px) { /* if width <= 780 */
                ${outline} {
                    display: none;
                }
            }
            `;

            outline.content = style.class`
            position: sticky;
            top: var(--Navbar_height);
            height: calc(100vh - var(--Navbar_height));
            `;

            const headeritem = style.class`
            cursor: pointer;
            -webkit-user-select: none;
            user-select: none;
            `;

            const path = style.class`
            display: flex;
            `;
            style`
            ${path} > li::after {
                content: "/";
                padding: 3px; 0;
            }
            `;

            return {
                wrapper,
                margin,
                sidebar,
                page,
                content,
                outline,
                headeritem,
                path,
            };
        });

        return style;
    }
);