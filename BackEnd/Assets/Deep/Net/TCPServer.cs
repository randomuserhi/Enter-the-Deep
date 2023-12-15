#nullable enable
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Deep.Net {

    public class TCPServer {
        private ArraySegment<byte> buffer;
        private Socket? socket;

        public Net.onAccept? onAccept;
        public Net.onReceive? onReceive;
        public Net.onDisconnect? onDisconnect;

        private ConcurrentDictionary<EndPoint, Socket> acceptedConnections = new ConcurrentDictionary<EndPoint, Socket>();

        public TCPServer(ArraySegment<byte> buffer) {
            this.buffer = buffer;
        }

        private void Open() {
            if (socket != null) Dispose();
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.ReuseAddress, true);
        }

        public EndPoint Bind(EndPoint remoteEP, int backlog = 5) {
            Open();
            socket!.Bind(remoteEP);
            socket!.Listen(backlog);
            _ = Listen(); // NOTE(randomuserhi): Start listen loop, not sure if `Bind` should automatically start the listen loop
            return socket.LocalEndPoint!;
        }

        private async Task Listen() {
            if (socket == null) return;
            Socket incomingConnection = await socket.AcceptAsync().ConfigureAwait(false);

            EndPoint? remoteEndPoint = incomingConnection.RemoteEndPoint;
            if (remoteEndPoint != null) {
                acceptedConnections.AddOrUpdate(remoteEndPoint, incomingConnection, (key, old) => { incomingConnection.Dispose(); return old; });
                onAccept?.Invoke(remoteEndPoint);
                _ = ListenTo(incomingConnection);
            } else {
                incomingConnection.Dispose();
            }

            _ = Listen(); // Start new listen task => async loop
        }

        private async Task ListenTo(Socket socket) {
            try {
                int receivedBytes = await socket.ReceiveAsync(buffer, SocketFlags.None).ConfigureAwait(false);
                EndPoint remoteEP = socket.RemoteEndPoint!;
                if (receivedBytes > 0) {
                    onReceive?.Invoke(receivedBytes, remoteEP);
                    _ = ListenTo(socket); // Start new listen task => async loop
                } else {
                    Dispose(socket);
                    onDisconnect?.Invoke(remoteEP);
                }
            } catch (ObjectDisposedException) {
                // NOTE(randomuserhi): Socket was disposed during ReceiveAsync
                Dispose(socket);
            }
        }

        private void Dispose(Socket socket) {
            socket.Dispose();
            acceptedConnections.Remove(socket.RemoteEndPoint!, out _);
        }

        public async Task Send(byte[] data) {
            List<Task> tasks = new List<Task>();
            foreach (EndPoint remoteEP in acceptedConnections.Keys) {
                tasks.Add(SendTo(data, remoteEP));
            }
            await Task.WhenAll(tasks).ConfigureAwait(false);
        }

        public async Task<int> SendTo(byte[] data, EndPoint remoteEP) {
            if (acceptedConnections.TryGetValue(remoteEP, out Socket? socket)) {
                try {
                    return await socket.SendAsync(data, SocketFlags.None).ConfigureAwait(false);
                } catch (SocketException) {
                    return 0;
                }
            }
            return 0;
        }

        public void Disconnect() {
            Dispose();
        }

        public void Dispose() {
            if (socket == null) return;

            socket.Dispose();
            socket = null;

            foreach (Socket? connection in acceptedConnections.Values) {
                connection.Dispose();
            }
            acceptedConnections.Clear();
        }
    }
}
