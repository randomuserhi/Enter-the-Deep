// TODO(randomuserhi): Documentation

(function() {
    type context = Docuscript.docuscript.Context;
    type node<T extends keyof Docuscript.docuscript.NodeMap | undefined = undefined> = Docuscript.docuscript.Node<T>;
    let defaultParser: Docuscript.Parser<Docuscript.docuscript.Language> = {
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

    let docuscript = window.docuscript = function<T extends string>(generator: (nodes: T) => void, parser: Docuscript.Parser<T> = defaultParser as any): Docuscript.Page<T> {
        const page: Docuscript.Page<T> = {
            parser,
            content: []
        };
        const nodes: any = {};
        const context: any = {};
        for (const [node, func] of Object.entries(parser as Docuscript.Parser<string>)) {
            nodes[node as keyof typeof nodes] = (...args: any[]) => 
                func.create.call(docuscriptContext, ...args);

            context[node as keyof typeof context] = (...args: any[]) => { 
                const node = func.create.call(docuscriptContext, ...args); 
                page.content.push(node); // auto-mount node
                return node;
            }
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
        generator(context);
        return page;
    } as Docuscript;

    docuscript.render = function<T extends string>(page: Docuscript.Page<T>) {
        const fragment = new DocumentFragment();
        const parser = page.parser;

        let stack: Node[] = [];
        let walk = (node: Docuscript._Node<T>) => {
            let dom = parser[node.__type__].parse(node as any);
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
                fragment.append(parser[node.__type__].parse(node as any));
                continue;
            }
            walk(node);
        }

        return fragment;
    };

    docuscript.defaultParser = defaultParser;
})();