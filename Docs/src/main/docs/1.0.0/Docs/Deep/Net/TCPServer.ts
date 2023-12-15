RHU.require(new Error(), { 
    docs: "docs", rhuDocuscript: "docuscript",
}, function({
    docs, rhuDocuscript,
}) {
    docs.jit = (version, path) => docuscript<RHUDocuscript.Language, RHUDocuscript.FuncMap>(({
        p, h, br, icode, code, link, pl, ot
    }) => {
        h(1, "Definition");
        p("Namespace: ", icode([], "Deep"));
        br();
        p("Creates a TCP server.");
        code(["csharp"], "public class TCPServer");

        h(1, "Constructors");
        ot({ widths: ["33%"] }, 
            ["signature", "summary"],
            {
                signature: pl([`${path}/Constructors`], "TCPServer(ArraySegment<byte>)"),
                summary: "Initialises a TCPServer with a given memory buffer.",
            },
        );

        h(1, "Methods");
        ot({ widths: ["33%"] }, 
            ["signature", "summary"],
            {
                signature: pl([`${path}/Bind`], "Bind(EndPoint)"),
                summary: "Binds a to a local end point.",
            },
            {
                signature: pl([`${path}/Send`], "Send(byte[])"),
                summary: "Sends bytes to all remote endpoints.",
            },
            {
                signature: pl([`${path}/SendTo`], "SendTo(byte[], IPEndPoint)"),
                summary: "Sends bytes to a specfic endpoint.",
            },
            {
                signature: pl([`${path}/Disconnect`], "Disconnect()"),
                summary: "Disconnects and disposes of the server and its internal socket.",
            },
            {
                signature: pl([`${path}/Dispose`], "Dispose()"),
                summary: "Disconnects and disposes of the server and its internal socket.",
            },
        );
    }, rhuDocuscript);
});