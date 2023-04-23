(function() {
    "use strict";

    let RHU = window.RHU;
    if (RHU === null || RHU === undefined) throw new Error("No RHU found. Did you import RHU before running?");
    RHU.module({ module: "navbar-content", hard: ["RHU.Macro"], trace: new Error() }, function()
    {
        let navbar = function()
        {
            let menuBtnClick = (function(e) {
                this.chevron.classList.toggle("js-active");
                if (this.chevron.classList.contains("js-active"))
                    this.openMenu();
                else
                    this.closeMenu();
            }).bind(this);
            this.menuBtn.onclick = menuBtnClick;
            this.githubBtn.onclick = (e) => {
                if (window.matchMedia("screen and (max-width: 780px)").matches)
                {
                    menuBtnClick();
                    return;
                }
                console.log("open profile");
            };

            let resize = (function() {
                if (!window.matchMedia("screen and (max-width: 780px)").matches)
                {
                    this.chevron.classList.remove("js-active");
                    this.closeMenu();
                }
            }).bind(this);
            window.addEventListener("resize", resize);
            resize();
        };
        navbar.prototype.openMenu = function()
        {
            console.log("open");
        };
        navbar.prototype.closeMenu = function()
        {
            console.log("close");
        };
        new RHU.Macro(navbar, "navbar-content",
            /*HTML*/`
            <nav class="Navbar-Controls">
                <div>
                    <button class="Navbar-Controls-DropDown">
                        Blogs
                        <svg style="height: 1.3rem;" viewBox="0 0 24 24" fill="currentColor">
                            <path fill-rule="evenodd" clip-rule="evenodd" d="M12.5303 15.5303C12.2374 15.8232 11.7626 15.8232 11.4697 15.5303L5.46967 9.53033C5.17678 9.23744 5.17678 8.76256 5.46967 8.46967C5.76256 8.17678 6.23744 8.17678 6.53033 8.46967L12 13.9393L17.4697 8.46967C17.7626 8.17678 18.2374 8.17678 18.5303 8.46967C18.8232 8.76256 18.8232 9.23744 18.5303 9.53033L12.5303 15.5303Z"/>
                        </svg>
                    </button>
                </div>
                <a>What's New</a>
            </nav>
            <!-- Spacer -->
            <div style="flex: 1;"></div>
            <button rhu-id="menuBtn" class="Navbar-Menu">
                <span rhu-id="chevron" class="Navbar-Menu_button"></span>
            </button>
            <button rhu-id="githubBtn" class="Navbar-ProfileMenu">
                <div>
                    <div style="position: relative; display: inline-block;">
                        <!-- profile image -->
                        <img rhu-id="avatar" class="Navbar-Avatar" src="https://avatars.githubusercontent.com/u/40913834?s=40&v=4"/>
                        <!-- notification circle -->
                        <span rhu-id="notif" class="Navbar-Avatar-Notif"></span>
                    </div>
                    <!-- dropdown -->
                    <svg class="Navbar-ProfileMenu_dropdown" style="height: 1.3rem;" viewBox="0 0 24 24" fill="currentColor">
                        <path fill-rule="evenodd" clip-rule="evenodd" d="M12.5303 15.5303C12.2374 15.8232 11.7626 15.8232 11.4697 15.5303L5.46967 9.53033C5.17678 9.23744 5.17678 8.76256 5.46967 8.46967C5.76256 8.17678 6.23744 8.17678 6.53033 8.46967L12 13.9393L17.4697 8.46967C17.7626 8.17678 18.2374 8.17678 18.5303 8.46967C18.8232 8.76256 18.8232 9.23744 18.5303 9.53033L12.5303 15.5303Z"/>
                    </svg>
                </div>
            </button>
            `,
            { floating: true });
    });
})();