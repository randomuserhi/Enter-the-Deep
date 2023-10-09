interface Docuscript {
    (name: string, generator: (nodes: Docuscript.ParserNodes<Docuscript.docuscript.Parser>) => void): Docuscript.Page<Docuscript.docuscript.Parser>;
    <T extends Docuscript.NodeDefinitionMap>(name: string, generator: (nodes: Docuscript.ParserNodes<T>) => void, parser: Docuscript.Parser<T>): Docuscript.Page<T>;
    defaultParser: Docuscript.Parser<Docuscript.docuscript.Parser>;
    pages: Map<String, Docuscript.Page<any>>;
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
    type NodeDefinitionMap = { [k in string]: NodeDefinition };
    interface NodeDefinition<T extends (...args: any[]) => any = (...args: any[]) => any> {
        create: T;
        parse: (node: AnyNode) => globalThis.Node;
    }

    interface Context<T extends NodeDefinitionMap> {
        page: Page<T>;
        nodes: {
            [P in keyof T]: T[P]["create"];
        };
        remount: (child: Node<T>, parent: Node<T>) => void;
    }

    type Parser<T extends NodeDefinitionMap> = {
        [P in keyof T]: {
            create: T[P]["create"];
            parse: (node: ReturnType<T[P]["create"]>) => globalThis.Node; 
        }
    };
    type ParserNodes<T extends NodeDefinitionMap> = {
        [P in keyof T]: T[P]["create"];
    }

    interface Page<T extends NodeDefinitionMap> {
        name: string;
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
            text: NodeDefinition<(text: string) => Node<"text">>;
            br: NodeDefinition<() => Node<"br">>;
            p: NodeDefinition<(...children: (string | Node)[]) => Node<"p">>;
            
            h: NodeDefinition<(heading: number, ...children: (string | Node)[]) => Node<"h">>;
    
            block: NodeDefinition<(...children: (string | Node)[]) => Node<"block">>;
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