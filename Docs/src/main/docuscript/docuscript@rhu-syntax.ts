declare namespace RHU {
    interface Modules {
        "docuscript": Docuscript.Parser<RHUDocuscript.Parser>;
    }
}

declare namespace RHUDocuscript {
    interface Parser extends Docuscript.NodeDefinitionMap {
        img: (src: string) => Node<"img">;
        text: (text: string) => Node<"text">;
        br: () => Node<"br">;
        p: (...children: (string | Node)[]) => Node<"p">;
        
        h: (heading: number, ...children: (string | Node)[]) => Node<"h">;
    
        block: (...children: (string | Node)[]) => Node<"block">;
    }

    interface NodeMap {
        img: {
            src: string;
        };
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
        img: {
            create: function(src) {
                return {
                    __type__: "img",
                    src: src,
                }
            },
            parse: function(node) {
                let img = document.createElement("img");
                img.src = node.src;
                return img;
            }
        },
        text: {
            create: function(text) {
                return {
                    __type__: "text",
                    text: text,
                };
            },
            parse: function(node) {
                return document.createTextNode(node.text);
            }
        },
        br: {
            create: function() {
                return {
                    __type__: "br",
                };
            },
            parse: function() {
                return document.createElement("br");
            }
        },
        p: {
            create: function(this: context, ...children) {
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
            parse: function() {
                return document.createElement("p");
            }
        },
        h: {
            create: function(this: context, heading, ...children) {
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
            parse: function(node) {
                return document.createElement(`h${node.heading}`);
            }
        },
        block: {
            create: function(this: context, ...children) {
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
            parse: function() {
                return document.createElement("div");
            }
        },
    };
});