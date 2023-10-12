declare namespace RHU {
    interface Modules {
        "docs": DocCollection;
    }
}

interface DocCollection {
    "0.0.1": Docs;
}

interface Docs {

}

RHU.module(new Error(), "docs", { 
}, function({}) {

    return {
        "0.0.1": {}
    };
});