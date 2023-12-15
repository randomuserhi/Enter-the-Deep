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
        p("Creates a UDP client.");
        code(["csharp"], "public class UDPClient");

        h(1, "Constructors");
        ot({ widths: ["33%"] }, 
            ["signature", "summary"],
            {
                signature: pl([`${path}/Constructors`], "UDPClient(ArraySegment<byte>)"),
                summary: "Initialises a UDPClient with a given memory buffer.",
            },
        );

        h(1, "Methods");
        ot({ widths: ["33%"] }, 
            ["signature", "summary"],
            {
                signature: pl([`${path}/Connect`], "Connect(EndPoint)"),
                summary: "Connects to a remote endpoint.",
            },
            {
                signature: pl([`${path}/Send`], "Send(byte[])"),
                summary: "Sends bytes to the remote endpoint.",
            },
            {
                signature: pl([`${path}/Disconnect`], "Disconnect()"),
                summary: "Disconnects and disposes of the client and its internal socket.",
            },
            {
                signature: pl([`${path}/Dispose`], "Dispose()"),
                summary: "Disconnects and disposes of the client and its internal socket.",
            },
        );
    }, rhuDocuscript);
});