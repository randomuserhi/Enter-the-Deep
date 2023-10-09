interface Docuscript {
    (name: string, generator: (nodes: Docuscript.docuscript.Parser) => void): Docuscript.Page<Docuscript.docuscript.Parser>;
    <T extends Docuscript.Record>(name: string, generator: (nodes: T) => void, parser: Docuscript.Parser<T>): Docuscript.Page<T>;
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
    type Record = { [k in string]: (...args: any[]) => any };

    interface Context<T extends Record> {
        page: Page<T>;
        nodes: {
            [P in keyof T]: T[P];
        };
        remount: (child: Node<T>, parent: Node<T>) => void;
    }

    interface Parser<T extends Record> {
        nodes: {
            [P in keyof T]: T[P];
        };
        parsers: {
            [P in keyof T]: (node: ReturnType<T[P]>) => globalThis.Node; 
        };
    }

    interface Page<T extends Record> {
        name: string;
        parser: Parser<T>;
        content: Node<T>[];
    }

    type Node<Parser extends Record, T = {}> = {
        __type__: keyof Parser,
        __children__?: Node<Parser>[],
        __parent__?: Node<Parser>,
        [x: string]: any,
    } & T;

    namespace docuscript {
        interface Parser extends Record {
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