interface Docuscript {
    (generator: (nodes: Docuscript.ParserNodes<Docuscript.docuscript.Language>) => void): Docuscript.docuscript.Page;
    <T extends string, FuncMap extends Docuscript.NodeFuncMap<T>>(generator: (nodes: Docuscript.ParserNodes<T>) => void, parser: Docuscript.Parser<T, FuncMap>): Docuscript.Page<T, FuncMap>;
    defaultParser: Docuscript.docuscript.Parser;
    render(page: Docuscript.Page<any, any>): DocumentFragment;
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
    type NodeFuncMap<T extends string> = { [K in T]: (...args: any[]) => any; };
    interface NodeDefinition<T extends (...args: any[]) => any = (...args: any[]) => any> {
        create: T;
        parse: (node: AnyNode) => globalThis.Node;
    }
    type ToNodeMap<T extends { [k in string]: (...args: any[]) => any }> = {
        [K in keyof T]: NodeDefinition<T[K]>;
    };

    interface Context<T extends string, FuncMap extends NodeFuncMap<T>> {
        page: Page<T, FuncMap>;
        nodes: {
            [P in keyof NodeFuncMap<T>]: ToNodeMap<FuncMap>[P]["create"];
        };
        remount: (child: _Node<T>, parent: _Node<T>) => void;
    }

    type Parser<T extends string, FuncMap extends NodeFuncMap<T>> = {
        [P in T]: {
            create: ToNodeMap<FuncMap>[P]["create"];
            parse: (node: ReturnType<ToNodeMap<FuncMap>[P]["create"]>) => globalThis.Node; 
        }
    };
    type ParserNodes<T extends string> = {
        [P in keyof NodeFuncMap<T>]: ToNodeMap<NodeFuncMap<T>>[P]["create"];
    }

    interface Page<T extends string, FuncMap extends NodeFuncMap<T>> {
        parser: Parser<T, FuncMap>;
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

        interface FuncMap extends NodeFuncMap<Language> {
            text: (text: string) => Node<"text">;
            br: () => Node<"br">;
            p: (...children: (string | Node)[]) => Node<"p">;
            
            h: (heading: number, ...children: (string | Node)[]) => Node<"h">;
    
            block: (...children: (string | Node)[]) => Node<"block">;
        }

        type Page = Docuscript.Page<Language, FuncMap>;
        type Parser = Docuscript.Parser<Language, FuncMap>;
        type Context = Docuscript.Context<Language, FuncMap>;
        type Node<T extends Language | undefined = undefined> = Docuscript.Node<NodeMap, T>;
    }
}