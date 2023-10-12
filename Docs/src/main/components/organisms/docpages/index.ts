declare namespace RHU {
    interface Modules {
        "components/organisms/docpages": "organisms/docpages";
    }

    namespace Macro {
        interface TemplateMap {
            "organisms/docpages": Organisms.Docpages;
        }
    }
}

declare namespace Organisms {
    interface Docpages extends HTMLDivElement {
        view(version: string, page: string): void;
        render(page: RHUDocuscript.Page): void;

        content: HTMLDivElement;
        filterlist: Molecules.Filterlist;

        currentPage: string;
        currentVersion: string;
    }
}

RHU.module(new Error(), "components/organisms/docpages", { 
    Macro: "rhu/macro", style: "components/organsisms/docpages/style",
    filterlist: "components/molecules/filterlist",
    rhuDocuscript: "docuscript", docs: "docs",
}, function({ 
    Macro, style,
    filterlist,
    rhuDocuscript,
    docs,
}) {
    const a = docs.create("0.0.1");
    a.pages.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({ 
        h, div, br, img,
    }) => {
        h(1, "This is a heading 0.0.1");
        img("https://avatars.githubusercontent.com/u/40913834?s=40&v=4");

        for (let i = 0; i < 20; ++i) {
            div(
                "This is a paragraph",
                "multiline?",
                br(),
                `no idea how this
                will
                render so...`,
                div(
                    "nested blocks"
                )
            );
        }
    }, rhuDocuscript));

    const b = docs.create("0.0.2");
    b.pages.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({ 
        h, div, br, img,
    }) => {
        h(1, "This is a heading 0.0.2");
        img("https://avatars.githubusercontent.com/u/40913834?s=40&v=4");

        for (let i = 0; i < 20; ++i) {
            div(
                "This is a paragraph",
                "multiline?",
                br(),
                `no idea how this
                will
                render so...`,
                div(
                    "nested blocks"
                )
            );
        }
    }, rhuDocuscript));

    const PageNotFound = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "Page not found.");
    }, rhuDocuscript);

    const VersionNotFound = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "Version not found.");
    }, rhuDocuscript);

    const docpages = Macro((() => {
        const docpages = function(this: Organisms.Docpages) {

            this.filterlist.version.addEventListener("change", () => {
                this.currentVersion = this.filterlist.version.value;
                this.view(this.currentVersion, this.currentPage);
            });
            
            this.currentPage = "home";
            this.currentVersion = this.filterlist.version.value;
            this.view(this.currentVersion, this.currentPage);

        } as RHU.Macro.Constructor<Organisms.Docpages>;

        docpages.prototype.render = function(page) {
            this.content.replaceChildren(docuscript.render(page));
        }

        docpages.prototype.view = function(versionStr, pageStr) {
            this.currentVersion = versionStr;
            this.currentPage = pageStr;
            const version = docs.get(this.currentVersion);
            if (RHU.exists(version)) {
                const page = version.pages.get(this.currentPage);
                if (RHU.exists(page)) {
                    this.render(page);
                } else {
                    this.render(PageNotFound);
                }
            } else {
                this.render(VersionNotFound);
            }
        }

        return docpages;
    })(), "organisms/docpages", //html
        `
        <div class="${style.margin}">
            <rhu-macro rhu-id="filterlist" class="${style.sidebar}" rhu-type="${filterlist}"></rhu-macro>
            <div class="${style.content}">
                <div>title?</div>
                <div rhu-id="content"></div>
            </div>
        </div>
        `, {
            element: //html
            `<div class="${style.wrapper}"></div>`
        });

    return docpages;
});