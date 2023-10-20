declare namespace RHU {
    interface Modules {
        "docs/indices": {
            DOCUSCRIPT_ROOT: string;
        };
    }
}

(() => {
    let DOCUSCRIPT_ROOT = "";
    if (document.currentScript) {
        let s = document.currentScript as HTMLScriptElement;
        let r = s.src.match(/(.*)[/\\]/);
        if (r)
            DOCUSCRIPT_ROOT = r[1] || "";
    } else {
        throw new Error("Failed to get document root.");
    }

    RHU.module(new Error(), "docs/indices", { 
        docs: "docs",
    }, function({
        docs,
    }) {
        
        const a = docs.create("1.0.0");
        a.set("home", "home.js");
        a.set("about", "about.js");

        return {
            DOCUSCRIPT_ROOT
        };
    });
})();