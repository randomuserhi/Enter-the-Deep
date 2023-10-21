RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const path = "home/nested";
    
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h,
    }) => {
        h(1, "1.0.0/home/nested");
    }, rhuDocuscript);
    docs.get(version)!.setCache(path, page);
    return page;
});