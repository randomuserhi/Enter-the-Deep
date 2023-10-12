interface Docuscript {
    (generator: (nodes: Docuscript.ParserNodes<Docuscript.docuscript.Language>) => void): Docuscript.Page<Docuscript.docuscript.Language>;
    <T extends string>(generator: (nodes: Docuscript.ParserNodes<T>) => void, parser: Docuscript.Parser<T>): Docuscript.Page<T>;
    defaultParser: Docuscript.Parser<Docuscript.docuscript.Language>;
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
    type NodeDefinitionMap<T extends string> = { [K in T]: (...args: any[]) => any; };
    interface NodeDefinition<T extends (...args: any[]) => any = (...args: any[]) => any> {
        create: T;
        parse: (node: AnyNode) => globalThis.Node;
    }
    type ToNodeMap<T extends { [k in string]: (...args: any[]) => any }> = {
        [K in keyof T]: NodeDefinition<T[K]>;
    };

    interface Context<T extends string> {
        page: Page<T>;
        nodes: {
            [P in keyof NodeDefinitionMap<T>]: ToNodeMap<NodeDefinitionMap<T>>[P]["create"];
        };
        remount: (child: _Node<T>, parent: _Node<T>) => void;
    }

    type Parser<T extends string> = {
        [P in keyof NodeDefinitionMap<T>]: {
            create: ToNodeMap<NodeDefinitionMap<T>>[P]["create"];
            parse: (node: ReturnType<ToNodeMap<NodeDefinitionMap<T>>[P]["create"]>) => globalThis.Node; 
        }
    };
    type ParserNodes<T extends string> = {
        [P in keyof NodeDefinitionMap<T>]: ToNodeMap<NodeDefinitionMap<T>>[P]["create"];
    }

    interface Page<T extends string> {
        parser: Parser<T>;
        content: _Node<T>[];
    }

    type _Node<T, Content = {}> = {
        __type__: T,
        __children__?: _Node<T>[],
        __parent__?: _Node<T>,
        [x: string]: any,
    } & Content;

    type Node<NodeMap, T> = _Node<T extends keyof NodeMap ? T : keyof NodeMap, T extends keyof NodeMap ? NodeMap[T] : {}>;

    namespace docuscript {
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
        type Language = keyof NodeMap;

        interface Parser extends NodeDefinitionMap<Language> {
            text: (text: string) => Node<"text">;
            br: () => Node<"br">;
            p: (...children: (string | Node)[]) => Node<"p">;
            
            h: (heading: number, ...children: (string | Node)[]) => Node<"h">;
    
            block: (...children: (string | Node)[]) => Node<"block">;
        }

        type Context = Docuscript.Context<Language>;
        type Node<T extends Language | undefined = undefined> = Docuscript.Node<NodeMap, T>;
    }
}