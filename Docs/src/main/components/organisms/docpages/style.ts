declare namespace RHU {
    interface Modules {
        "components/organsisms/docpages/style": {
            wrapper: Style.ClassName;
        };
    }
}

RHU.module(new Error(), "components/organsisms/docpages/style",
    { Style: "rhu/style", theme: "main/theme" },
    function({ Style, theme })
    {
        const style = Style(({ style }) => {
            const wrapper = style.class`
                display: flex;
                gap: 10px;
            `;
            return {
                wrapper
            };
        });

        return style;
    }
);