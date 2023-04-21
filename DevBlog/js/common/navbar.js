(function() {
    "use strict";

    // TODO(randomuserhi): move styles into classes and change colors into theme variables

    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "navbar", hard: ["RHU.Macro"], trace: new Error() }, function()
    {
        let navbar = function() {};
        new RHU.Macro(navbar, "navbar",
            /*HTML*/`
            <nav class="Navbar-Margin">
                <!-- LOGO -->
                <svg class="Navbar-Logo" viewBox="0 0 26 15" fill="currentColor">
                    <path fill-rule="evenodd" clip-rule="evenodd" d="m5 0-5 15 6 0 5-15-6 0m10 15 5-15 6 0-5 15-6 0"/>
                </svg>
                <rhu-macro rhu-type="navbar-content"></rhu-macro>
            </nav>
            `,
            { element: /*HTML*/`<header class="Navbar"></header>` });

    });
})();