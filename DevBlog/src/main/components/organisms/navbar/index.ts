declare namespace RHU {
    interface Modules {
        "navbar": "navbar";
    }

    namespace Macro {
        interface TemplateMap
        {
            "navbar": navbar;
        }
    }
}

interface navbar extends HTMLDivElement
{
}
interface navbarConstructor extends RHU.Macro.Constructor<navbar>
{
    
}

RHU.module(new Error(), "navbar",
    { Macro: "rhu/macro", Style: "rhu/style", style: "navbar/style" },
    function({ Macro, Style, style })
    {
        const _navbar = function(this: appmount)
        {
            
        } as appmountConstructor;
        
        const navbar = Macro(_navbar, "navbar", //html
            `
            <nav class="${style.margin}">
                <!-- LOGO -->
                <svg class="${style.logo}" viewBox="0 0 26 15" fill="currentColor">
                    <path fill-rule="evenodd" clip-rule="evenodd" d="m5 0-5 15 6 0 5-15-6 0m10 15 5-15 6 0-5 15-6 0"/>
                </svg>
                <nav class="${style.controls}">
                    <div>
                        <button class="${style.controls.dropdown}">
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
                <button rhu-id="menuBtn" class="${style.menu}">
                    <span rhu-id="chevron" class="${style.menu.button}"></span>
                </button>
                <button rhu-id="githubBtn" class="${style.profile}">
                    <div>
                        <div style="position: relative; display: inline-block;">
                            <!-- profile image -->
                            <img rhu-id="avatar" class="${style.profile.avatar}" src="https://avatars.githubusercontent.com/u/40913834?s=40&v=4"/>
                            <!-- notification circle -->
                            <span rhu-id="notif" class="${style.profile.avatar.notif}"></span>
                        </div>
                        <!-- dropdown -->
                        <svg class="${style.profile.dropdown}" style="height: 1.3rem;" viewBox="0 0 24 24" fill="currentColor">
                            <path fill-rule="evenodd" clip-rule="evenodd" d="M12.5303 15.5303C12.2374 15.8232 11.7626 15.8232 11.4697 15.5303L5.46967 9.53033C5.17678 9.23744 5.17678 8.76256 5.46967 8.46967C5.76256 8.17678 6.23744 8.17678 6.53033 8.46967L12 13.9393L17.4697 8.46967C17.7626 8.17678 18.2374 8.17678 18.5303 8.46967C18.8232 8.76256 18.8232 9.23744 18.5303 9.53033L12.5303 15.5303Z"/>
                        </svg>
                    </div>
                </button>
            </nav>
            `, {
                element: //html
                `<header class="${style.wrapper}"></header>`
            });

        return navbar;
    }
);