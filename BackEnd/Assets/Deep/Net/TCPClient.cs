﻿#nullable enable
using System;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

// TODO(randomuserhi): CancellationTokens on connect

namespace Deep.Net {

    public class TCPClient {
        private ArraySegment<byte> buffer;
        private Socket? socket;

        public Net.onConnect? onConnect;
        public Net.onReceive? onReceive;
        public Net.onDisconnect? onDisconnect;

        public TCPClient(ArraySegment<byte> buffer) {
            this.buffer = buffer;
        }

        private void Open() {
            if (socket != null) Dispose();
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.ReuseAddress, true);
        }

        public async Task Connect(EndPoint remoteEP) {
            Open();
            await socket!.ConnectAsync(remoteEP).ConfigureAwait(false);
            onConnect?.Invoke(remoteEP);
            _ = Listen(); // NOTE(randomuserhi): Start listen loop, not sure if `Connect` should automatically start the listen loop
        }

        private async Task Listen() {
            if (socket == null) return;
            try {
                int receivedBytes = await socket.ReceiveAsync(buffer, SocketFlags.None).ConfigureAwait(false);
                EndPoint remoteEP = socket.RemoteEndPoint!;
                if (receivedBytes > 0) {
                    onReceive?.Invoke(receivedBytes, remoteEP);
                    _ = Listen(); // Start new listen task => async loop
                } else {
                    Dispose();
                    onDisconnect?.Invoke(remoteEP);
                }
            } catch (ObjectDisposedException) {
                // NOTE(randomuserhi): Socket was disposed during ReceiveAsync
            }
        }

        public async Task<int> Send(byte[] data) {
            if (socket == null) return 0;
            try {
                return await socket.SendAsync(data, SocketFlags.None).ConfigureAwait(false);
            } catch (SocketException) {
                return 0;
            }
        }

        public void Disconnect() {
            Dispose();
        }

        public void Dispose() {
            if (socket == null) return;

            socket.Dispose();
            socket = null;
        }
    }
}