interface Docuscript {
    <T extends {} = Docuscript.Nodes>(name: string, generator: (nodes: T) => void, parser?: Docuscript.Parser): Docuscript.Page;
    defaultParser: Docuscript.Parser;
    pages: Map<String, Docuscript.Page>;
    render(page: Docuscript.Page): DocumentFragment;
}

declare var docuscript: Docuscript;
interface Window {
    docuscript: Docuscript;
}

declare namespace Docuscript {
    interface Parser<T extends {} = Nodes> {
        nodes: {
            [P in keyof T]: T[P];
        };
        parsers: {
            [P in keyof T]: (node: ReturnType<T[P]>) => DocumentFragment; 
        };
    }

    interface Page {
        name: string;
        parser: Parser;
        content: Node[];
    }

    type Node<T = {}, Parser extends {} = Nodes> = {
        __type__: keyof Parser,
        __children__?: Node[],
        __parent__?: Node,
        [x: string]: any,
    } & T;

    interface Nodes {
        text: (text: string) => Node<text>;
        h: (heading: number, ...children: (string | Node)[]) => Node<h>;
        p: (...children: (string | Node)[]) => Node<p>;
    }

    interface text {
        text: string;
    }

    interface p {}

    interface h {
        heading: number;
    }
}