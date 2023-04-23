(function() {
    "use strict";

    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "main", hard: ["RHU.Macro"], trace: new Error() }, function()
    {
        
    });
})();