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

        currentPath: string;
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
    console.log(docs);
    
    const a = docs.create("0.0.1");
    a.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
    }, rhuDocuscript));
    a.set("some/nested/file", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.1");
    }, rhuDocuscript));

    const b = docs.create("0.0.2");
    b.set("home", docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h
    }) => {
        h(1, "0.0.2");
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

    const DirectoryPage = (directory: Page) => {
        return docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({

        }) => {

        }, rhuDocuscript);
    }

    const docpages = Macro((() => {
        const docpages = function(this: Organisms.Docpages) {

            this.filterlist.version.addEventListener("change", () => {
                this.currentVersion = this.filterlist.version.value;
                this.view(this.currentVersion, this.currentPath);
            });
            
            this.currentPath = "home";
            this.currentVersion = this.filterlist.version.value;
            this.view(this.currentVersion, this.currentPath);

        } as RHU.Macro.Constructor<Organisms.Docpages>;

        docpages.prototype.render = function(page) {
            this.content.replaceChildren(docuscript.render(page));
        }

        docpages.prototype.view = function(versionStr, pageStr) {
            this.currentVersion = versionStr;
            this.currentPath = pageStr;
            const version = docs.get(this.currentVersion);
            if (RHU.exists(version)) {
                const directory = version.get(this.currentPath);
                if (RHU.exists(directory)) {
                    if (RHU.exists(directory.page)) {
                        this.render(directory.page);
                    } else {
                        this.render(DirectoryPage(directory));
                    }
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
            <div class="${style.page}">
                <div class="${style.content}">
                    <div>title?</div>
                    <div rhu-id="content"></div>
                </div>
                <div class="${style.outline}">
                    In this article
                </div>
            </div>
        </div>
        `, {
            element: //html
            `<div class="${style.wrapper}"></div>`
        });

    return docpages;
});