#nullable enable
using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Deep.Net {
    // TODO(randomuserhi): https://web.archive.org/web/20160728022524/http://blog.dickinsons.co.za/tips/2015/06/01/Net-Sockets-and-You/
    //                     - better memory allocation strategy with ArraySegment<byte> to prevent fragmentation
    public class UDPServer {
        private ArraySegment<byte> buffer;
        private EndPoint remoteEndPoint = new IPEndPoint(IPAddress.Any, 0);
        private Socket? socket;

        public Net.onReceive? onReceive;

        public UDPServer(ArraySegment<byte> buffer) {
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

        public EndPoint Bind(EndPoint remoteEP) {
            Open();
            socket!.Bind(remoteEP);
            _ = Listen(); // NOTE(randomuserhi): Start listen loop, not sure if `Bind` should automatically start the listen loop
            return socket.LocalEndPoint!;
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
            //                     by default we expect any, hence `remoteEndPoint = new IPEndPoint(IPAddress.Any, 0)`
            SocketReceiveFromResult result = await socket!.ReceiveFromAsync(buffer, SocketFlags.None, remoteEndPoint).ConfigureAwait(false);
            onReceive?.Invoke(new ArraySegment<byte>(buffer.Array, buffer.Offset, result.ReceivedBytes), result.RemoteEndPoint);

            _ = Listen(); // Start new listen task => async loop
        }

        public async Task<int> Send(byte[] data) {
            if (socket == null) return 0;
            return await socket.SendAsync(data, SocketFlags.None).ConfigureAwait(false);
        }

        public async Task<int> SendTo(byte[] data, IPEndPoint destination) {
            if (socket == null) return 0;
            return await socket.SendToAsync(data, SocketFlags.None, destination).ConfigureAwait(false);
        }
    }
}
