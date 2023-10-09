// TODO(randomuserhi): Move into js3party and make standalone package

(function() {
    let defaultParser: Docuscript.Parser = {
        nodes: {
            text: function(this: Docuscript.Page, text) {
                let node: Docuscript.Node<Docuscript.text> = {
                    __type__: "text",
                    __children__: [],
                    text: text,
                };
                
                // mount node
                this.content.push(node);
                return node;
            },
            p: function(this: Docuscript.Page, ...children) {
                let node: Docuscript.Node<Docuscript.p> = {
                    __type__: "p",
                };
                
                let childNodes: Docuscript.Node[] = [];
                for (let child of children) {
                    let childNode: Docuscript.Node;
                    if (typeof child === "string") {
                        childNode = {
                            __type__: "text",
                            __children__: [],
                            text: child
                        };
                    } else {
                        childNode = child;
                    }
                    
                    // unmount child if mounted
                    if (childNode.__parent__ && childNode.__parent__.__children__) {
                        childNode.__parent__.__children__ = childNode.__parent__.__children__.filter(n => n !== childNode);
                    } else {
                        this.content = this.content.filter(n => n !== childNode);
                    }
                    childNode.__parent__ = node;
                    childNodes.push(childNode);
                }
                node.__children__ = childNodes;

                // mount node
                this.content.push(node);
                return node;
            },
            h: function(this: Docuscript.Page, heading, ...children) {
                let node: Docuscript.Node<Docuscript.h> = {
                    __type__: "h",
                    heading: heading,
                };
                
                let childNodes: Docuscript.Node[] = [];
                for (let child of children) {
                    let childNode: Docuscript.Node;
                    if (typeof child === "string") {
                        childNode = {
                            __type__: "text",
                            __children__: [],
                            text: child
                        };
                    } else {
                        childNode = child;
                    }
                    
                    // unmount child if mounted
                    if (childNode.__parent__ && childNode.__parent__.__children__) {
                        childNode.__parent__.__children__ = childNode.__parent__.__children__.filter(n => n !== childNode);
                    } else {
                        this.content = this.content.filter(n => n !== childNode);
                    }
                    childNode.__parent__ = node;
                    childNodes.push(childNode);
                }
                node.__children__ = childNodes;

                // mount node
                this.content.push(node);
                return node;
            }
        },
        parsers: {
            text: function(node) {
                return 
            }
        },
    };

    let docuscript = window.docuscript = function<T = Docuscript.Nodes>(name: string, generator: (nodes: T) => void, parser: Docuscript.Parser = defaultParser): Docuscript.Page {
        let page: Docuscript.Page = {
            name,
            parser,
            content: []
        };
        let context: any = {};
        for (const [node, func] of Object.entries(parser.nodes)) {
            context[node as keyof typeof context] = (...args: any[]) => func.call(page, ...args);
        }
        generator(context);
        pages.set(page.name, page);
        return page;
    } as Docuscript;

    docuscript.defaultParser = defaultParser;
    let pages = docuscript.pages = new Map<String, Docuscript.Page>();
})();