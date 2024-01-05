#nullable enable
using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

// TODO(randomuserhi): CancellationTokens on connect

namespace Deep.Net {
    // TODO(randomuserhi): https://web.archive.org/web/20160728022524/http://blog.dickinsons.co.za/tips/2015/06/01/Net-Sockets-and-You/
    //                     - better memory allocation strategy with ArraySegment<byte> to prevent fragmentation
    public class UDPClient {
        private ArraySegment<byte> buffer;
        private EndPoint remoteEndPoint = new IPEndPoint(IPAddress.Any, 0);
        private Socket? socket;

        public Net.onReceive? onReceive;

        public UDPClient(ArraySegment<byte> buffer) {
            this.buffer = buffer;
        }

        private void Open() {
            if (socket != null) socket.Dispose();
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.ReuseAddress, true);

            //https://stackoverflow.com/questions/38191968/c-sharp-udp-an-existing-connection-was-forcibly-closed-by-the-remote-host
            socket.IOControl(
                (IOControlCode)(-1744830452),
                new byte[] { 0, 0, 0, 0 },
                null
            );
        }

        public async Task Connect(EndPoint remoteEP) {
            Open();
            remoteEndPoint = remoteEP;
            await socket!.ConnectAsync(remoteEP).ConfigureAwait(false);
            _ = Listen(); // NOTE(randomuserhi): Start listen loop, not sure if `Connect` should automatically start the listen loop
        }

        public void Disconnect() {
            Dispose();
        }

        public void Dispose() {
            if (socket == null) return;

            socket.Dispose();
            socket = null;
        }

        private async Task Listen() {
            if (socket == null) return;

            // NOTE(randomuserhi): remote end point passed in here is the endpoint we expect data to be from.
            //                     by default we expect to only receive data from the connected endpoint, thus
            //                     `remoteEndPoint = remoteEP` from `this.Connect`
            SocketReceiveFromResult result = await socket.ReceiveFromAsync(buffer, SocketFlags.None, remoteEndPoint).ConfigureAwait(false);
            onReceive?.Invoke(new ArraySegment<byte>(buffer.Array, buffer.Offset, result.ReceivedBytes), result.RemoteEndPoint);

            _ = Listen(); // Start new listen task => async loop
        }

        public async Task<int> Send(byte[] data) {
            if (socket == null) return 0;
            return await socket.SendAsync(data, SocketFlags.None).ConfigureAwait(false);
        }
    }
}
