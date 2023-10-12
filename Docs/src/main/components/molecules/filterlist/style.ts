declare namespace RHU {
    interface Modules {
        "components/molecules/filterlist/style": {
            wrapper: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "components/molecules/filterlist/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            style/*css*/`
            :root
            {
                --Sidebar_width: 250px;
            }
            `;

            const wrapper = style.class`
            position: fixed;
            width: var(--Sidebar_width);
            background-color: #eee;
            height: 100%;
            `;
            
            return {
                wrapper,
            };
        });

        return style;
    }
);