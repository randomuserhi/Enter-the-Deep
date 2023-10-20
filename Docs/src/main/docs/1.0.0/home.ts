RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const path = "home";
    
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h,
    }) => {
        h(1, "1.0.0/home");
    }, rhuDocuscript);
    docs.get(version)!.setCache(path, page);
    return page;
});