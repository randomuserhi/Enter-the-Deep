(function() {
    "use strict";

    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "main", hard: ["RHU.Macro", "RHU.Markdown"], trace: new Error() }, function()
    {
        let content = function()
        {
            // parse page content or something idk
        };
        RHU.Macro(content, "content",
            /*HTML*/`
                Markdown gets inserted here...
            `,
            { element: /*HTML*/`<div></div>` });
    });
})();