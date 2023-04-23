(function() {
    "use strict";
    
    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "theme", hard: ["RHU.Theme"], trace: new Error() }, function()
    {
        let ThemeGroup = new RHU.Theme.Group("js-duqaTheme");
        ThemeGroup.themes.set("dark", {
            "DefaultColor": "rgba(255, 255, 255, 0.8)",

            "Navbar_bgColor": "black",
            "Navbar-Controls_color": "var(--js-DefaultColor)",
            "Navbar-Controls_hoverColor": "#2997ff",
            "Navbar-Controls-DropDown_hoverBgColor": "transparent",
            "Navbar-Controls-Button_color": "var(--js-DefaultColor)",
            "Navbar-Controls-Button_bgColor": "white",
            "Navbar-Controls-Button_hoverColor": "white",
            "Navbar-Controls-Button_hoverBgColor": "white",
            "Navbar-Controls-Login_color": "var(--js-DefaultColor)",
            "Navbar-Controls-Login_bgColor": "transparent",
            "Navbar-Controls-Login_hoverColor": "#2997ff",
            "Navbar-Controls-Login_hoverBgColor": "transparent",
            "Navbar-Controls-SignUp_color": "var(--js-DefaultColor)",
            "Navbar-Controls-SignUp_bgColor": "#0071e3",
            "Navbar-Controls-SignUp_hoverColor": "white",
            "Navbar-Controls-SignUp_hoverBgColor": "#147ce5",
            "Navbar-Controls-Profile_color": "var(--js-DefaultColor)",
            "Navbar-Controls-Profile_hoverColor": "white"
        });
        ThemeGroup.themes.set("light", {
        });
        ThemeGroup.ruleSet = ThemeGroup.themes.get("dark");
        ThemeGroup.mediaQueries.set("prefers-color-scheme: dark", ThemeGroup.themes.get("dark"));
        ThemeGroup.attach();
    });
})();