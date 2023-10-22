RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const path = "Deep Engine";
    
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h,
    }) => {
        h(1, "Deep Engine");
    }, rhuDocuscript);
    docs.get(version)!.setCache(path, page);
    return page;
});