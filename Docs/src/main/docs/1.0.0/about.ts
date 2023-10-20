RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const name = "about";
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h,
    }) => {
        h(1, "1.0.0/about");
    }, rhuDocuscript);
    docs.get(version)!.setCache(name, page);
    return page;
});