declare namespace RHU {
    interface Modules {
        "docuscript": Docuscript.Parser<RHUDocuscript.Parser>;
    }
}

declare namespace RHUDocuscript {
    interface Parser extends Docuscript.Record {
        text: (text: string) => Node<"text">;
        br: () => Node<"br">;
        p: (...children: (string | Node)[]) => Node<"p">;
        
        h: (heading: number, ...children: (string | Node)[]) => Node<"h">;
    
        block: (...children: (string | Node)[]) => Node<"block">;
    }

    interface NodeMap {
        text: {
            text: string;
        };
        br: {};
        p: {};
        h: {
            heading: number;
        };
        block: {};
    }

    type Context = Docuscript.Context<Parser>;
    type Node<T extends keyof NodeMap | undefined = undefined> = Docuscript.Node<Parser, T extends keyof NodeMap ? NodeMap[T] : {}>;
}

RHU.module(new Error(), "docuscript", { 
}, function({}) {
    type context = RHUDocuscript.Context;
    type node<T extends keyof RHUDocuscript.NodeMap | undefined = undefined> = RHUDocuscript.Node<T>;
    return {
        nodes: {
            text: function(this: context, text) {
                return {
                    __type__: "text",
                    text: text,
                };
            },
            br: function() {
                return {
                    __type__: "br",
                };
            },
            p: function(this: context, ...children) {
                let node: node<"p"> = {
                    __type__: "p",
                };

                for (let child of children) {
                    let childNode: node;
                    if (typeof child === "string") {
                        childNode = this.nodes.text(child);
                    } else {
                        childNode = child;
                    }
                    
                    this.remount(childNode, node);
                }

                return node;
            },
            h: function(this: context, heading, ...children) {
                let node: node<"h"> = {
                    __type__: "h",
                    heading: heading,
                };
                
                for (let child of children) {
                    let childNode: node;
                    if (typeof child === "string") {
                        childNode = this.nodes.text(child);
                    } else {
                        childNode = child;
                    }
                    
                    this.remount(childNode, node);
                }

                return node;
            },
            block: function(this: context, ...children) {
                let node: node<"block"> = {
                    __type__: "block",
                };
                
                for (let child of children) {
                    let childNode: node;
                    if (typeof child === "string") {
                        childNode = this.nodes.p(child);
                    } else {
                        childNode = child;
                    }
                    
                    this.remount(childNode, node);
                }

                return node;
            },
        },
        parsers: {
            text: function(node) {
                return document.createTextNode(node.text);
            },
            br: function() {
                return document.createElement("br");
            },
            p: function() {
                return document.createElement("p");
            },
            h: function(node) {
                return document.createElement(`h${node.heading}`);
            },
            block: function() {
                return document.createElement("div");
            },
        },
    };
});