// TODO(randomuserhi): Documentation

(function() {
    type context = Docuscript.docuscript.Context;
    type node<T extends keyof RHUDocuscript.NodeMap | undefined = undefined> = Docuscript.docuscript.Node<T>;
    let defaultParser: Docuscript.Parser<Docuscript.docuscript.Parser> = {
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

    let docuscript = window.docuscript = function<T extends Docuscript.Record = Docuscript.docuscript.Parser>(name: string, generator: (nodes: T) => void, parser: Docuscript.Parser<T> = defaultParser as any): Docuscript.Page<T> {
        const page: Docuscript.Page<T> = {
            name,
            parser,
            content: []
        };
        const nodes: any = {};
        for (const [node, func] of Object.entries(parser.nodes)) {
            nodes[node as keyof typeof nodes] = (...args: any[]) => 
                func.call(docuscriptContext, ...args);
        }
        const docuscriptContext: Docuscript.Context<T> = {
            page,
            nodes,
            remount: (child, parent) => {
                if (child.__parent__ && child.__parent__.__children__) {
                    child.__parent__.__children__ = child.__parent__.__children__.filter(n => n !== child);
                } else {
                    page.content = page.content.filter(n => n !== child);
                }
                child.__parent__ = parent;
                if (parent.__children__) {
                    parent.__children__.push(child);
                } else {
                    parent.__children__ = [child];
                }
            } 
        }
        const context: any = {};
        for (const [node, func] of Object.entries(parser.nodes)) {
            context[node as keyof typeof context] = (...args: any[]) => { 
                const node = func.call(docuscriptContext, ...args); 
                page.content.push(node); // auto-mount node
                return node;
            }
        }
        generator(context);
        pages.set(page.name, page);
        return page;
    } as Docuscript;

    docuscript.render = function<T extends Docuscript.Record>(page: Docuscript.Page<T>) {
        const fragment = new DocumentFragment();
        const parser = page.parser;

        let stack: Node[] = [];
        let walk = (node: Docuscript.Node<T>) => {
            let dom = parser.parsers[node.__type__](node as any);
            let parent = stack.length === 0 ? undefined : stack[stack.length - 1];

            stack.push(dom);

            if (node.__children__) {
                for (let child of node.__children__) {
                    walk(child);
                }
            }

            if (parent) {
                parent.appendChild(dom);
            } else {
                fragment.append(dom);
            }

            stack.pop();
        };
        for (let node of page.content) {
            if (!node.__children__ || node.__children__.length === 0) {
                fragment.append(parser.parsers[node.__type__](node as any));
                continue;
            }
            walk(node);
        }

        return fragment;
    };

    docuscript.defaultParser = defaultParser;
    let pages = docuscript.pages = new Map<String, Docuscript.Page<any>>();
})();