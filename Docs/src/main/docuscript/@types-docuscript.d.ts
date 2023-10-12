interface Docuscript {
    (generator: (nodes: Docuscript.ParserNodes<Docuscript.docuscript.Parser>) => void): Docuscript.Page<Docuscript.docuscript.Parser>;
    <T extends Docuscript.NodeDefinitionMap>(generator: (nodes: Docuscript.ParserNodes<T>) => void, parser: Docuscript.Parser<T>): Docuscript.Page<T>;
    defaultParser: Docuscript.Parser<Docuscript.docuscript.Parser>;
    render(page: Docuscript.Page<any>): DocumentFragment;
}

declare var docuscript: Docuscript;
interface Window {
    docuscript: Docuscript;
}

declare namespace Docuscript {
    type AnyNode = {  
        __type__: PropertyKey,
        __children__?: AnyNode[],
        __parent__?: AnyNode,
        [x: string]: any,
    };
    type NodeDefinitionMap = { [K in string]: (...args: any[]) => any; };
    interface NodeDefinition<T extends (...args: any[]) => any = (...args: any[]) => any> {
        create: T;
        parse: (node: AnyNode) => globalThis.Node;
    }
    type ToNodeMap<T extends { [k in string]: (...args: any[]) => any }> = {
        [K in keyof T]: NodeDefinition<T[K]>;
    };

    interface Context<T extends NodeDefinitionMap> {
        page: Page<T>;
        nodes: {
            [P in keyof T]: ToNodeMap<T>[P]["create"];
        };
        remount: (child: Node<T>, parent: Node<T>) => void;
    }

    type Parser<T extends NodeDefinitionMap> = {
        [P in keyof T]: {
            create: ToNodeMap<T>[P]["create"];
            parse: (node: ReturnType<ToNodeMap<T>[P]["create"]>) => globalThis.Node; 
        }
    };
    type ParserNodes<T extends NodeDefinitionMap> = {
        [P in keyof T]: ToNodeMap<T>[P]["create"];
    }

    interface Page<T extends NodeDefinitionMap> {
        parser: Parser<T>;
        content: Node<T>[];
    }

    type Node<Parser extends NodeDefinitionMap, T = {}> = {
        __type__: keyof Parser,
        __children__?: Node<Parser>[],
        __parent__?: Node<Parser>,
        [x: string]: any,
    } & T;

    namespace docuscript {
        interface Parser extends NodeDefinitionMap {
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
}