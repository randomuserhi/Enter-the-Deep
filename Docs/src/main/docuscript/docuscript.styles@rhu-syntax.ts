declare namespace RHU {
    interface Modules {
        "docuscript/style": {
            body: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "docuscript/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            const body = style.class`
            `;

            // HEADINGS
            style`
            ${body} h1 {
                font-size: 2.5rem;
                font-weight: 700;
            }
            ${body} h2 {
                font-size: 2rem;
                font-weight: 700;
            }
            ${body} h3 {
                font-size: 1.8rem;
                font-weight: 700;
            }
            ${body} h4 {
                font-size: 1.5rem;
                font-weight: 700;
            }
            ${body} h5 {
                font-size: 1.3rem;
                font-weight: 700;
            }
            ${body} h6 {
                font-size: 1.125rem;
                font-weight: 700;
            }
            `;

            return {
                body,
            };
        });

        return style;
    }
);