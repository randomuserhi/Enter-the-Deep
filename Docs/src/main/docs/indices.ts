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
        
        ((docs: Docs) => {
            docs.set("Deep Engine", "Deep Engine.js");
        })(docs.create("1.0.0", "Deep Engine"));

        return {
            DOCUSCRIPT_ROOT
        };
    });
})();