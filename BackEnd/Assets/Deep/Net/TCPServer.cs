#nullable enable
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Deep.Net {

    public class TCPServer {
        private int bufferSize;
        private Socket? socket;

        public Net.onAccept? onAccept;
        public Net.onReceive? onReceive;
        public Net.onDisconnect? onDisconnect;

        private class Connection : IDisposable {
            public Socket socket;
            public ArraySegment<byte> buffer;

            public Connection(Socket socket, ArraySegment<byte> buffer) {
                this.socket = socket;
                this.buffer = buffer;
            }

            public void Dispose() {
                socket.Dispose();
            }
        }
        private ConcurrentDictionary<EndPoint, Connection> acceptedConnections = new ConcurrentDictionary<EndPoint, Connection>();

        public TCPServer(int bufferSize) {
            this.bufferSize = bufferSize;
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
            Socket incoming = await socket.AcceptAsync().ConfigureAwait(false);

            EndPoint? remoteEndPoint = incoming.RemoteEndPoint;
            if (remoteEndPoint != null) {
                Connection connection = new Connection(incoming, new byte[bufferSize]);
                acceptedConnections.AddOrUpdate(remoteEndPoint, connection, (key, old) => { connection.Dispose(); return old; });
                onAccept?.Invoke(remoteEndPoint);
                _ = ListenTo(connection);
            } else {
                incoming.Dispose();
            }

            _ = Listen(); // Start new listen task => async loop
        }

        private async Task ListenTo(Connection connection) {
            try {
                Socket socket = connection.socket;
                int receivedBytes = await socket.ReceiveAsync(connection.buffer, SocketFlags.None).ConfigureAwait(false);
                EndPoint remoteEP = socket.RemoteEndPoint!;
                if (receivedBytes > 0) {
                    onReceive?.Invoke(receivedBytes, remoteEP);
                    _ = ListenTo(connection); // Start new listen task => async loop
                } else {
                    Dispose(connection);
                    onDisconnect?.Invoke(remoteEP);
                }
            } catch (ObjectDisposedException) {
                // NOTE(randomuserhi): Socket was disposed during ReceiveAsync
                Dispose(connection);
            }
        }

        private void Dispose(Connection connection) {
            acceptedConnections.Remove(connection.socket.RemoteEndPoint!, out _);
            connection.Dispose();
        }

        public async Task Send(ArraySegment<byte> data) {
            List<Task> tasks = new List<Task>();
            foreach (EndPoint remoteEP in acceptedConnections.Keys) {
                tasks.Add(SendTo(data, remoteEP));
            }
            await Task.WhenAll(tasks).ConfigureAwait(false);
        }

        public async Task<int> SendTo(ArraySegment<byte> data, EndPoint remoteEP) {
            if (acceptedConnections.TryGetValue(remoteEP, out Connection? connection)) {
                try {
                    return await connection.socket.SendAsync(data, SocketFlags.None).ConfigureAwait(false);
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

            foreach (Connection? connection in acceptedConnections.Values) {
                connection.Dispose();
            }
            acceptedConnections.Clear();
        }
    }
}
