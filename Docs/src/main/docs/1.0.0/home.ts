declare namespace RHU {
    interface Modules {
        "docs/1.0.0/home": RHUDocuscript.Page;
    }
}

RHU.module(new Error(), "docs/1.0.0/home", { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    const version = "1.0.0";
    const page = docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        h,
    }) => {
        h(1, "1.0.0/home");
    }, rhuDocuscript);
    docs.get(version)!.setCache("home", page);
    return page;
});