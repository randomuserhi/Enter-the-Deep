RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const path = "about";
    
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h, p
    }) => {
        h(1, "1.0.0/about");
        for (let i = 0; i < 100; ++i) {
            p("crazy");
        }
        h(2, "1.0.0/about");
        for (let i = 0; i < 100; ++i) {
            p("crazy");
        }
        h(1, "low");
    }, rhuDocuscript);
    docs.get(version)!.setCache(path, page);
    return page;
});