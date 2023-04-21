(function() {
    "use strict";
    
    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "theme", hard: ["RHU.Theme"], trace: new Error() }, function()
    {
        let ThemeGroup = new RHU.Theme.Group("js-duqaTheme");
        ThemeGroup.themes.set("light", {
        });
        ThemeGroup.ruleSet = ThemeGroup.themes.get("light");
        //ThemeGroup.mediaQueries.set("prefers-color-scheme: dark", ThemeGroup.themes.get("dark"));
        ThemeGroup.attach();
    });
})();