using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Net;

namespace Deep.Sock
{
    public class UDPSocket
    {
        private byte[] buffer;
        private EndPoint endPoint = new IPEndPoint(IPAddress.Any, 0);
        private Socket socket;

        public AsyncCallback onreceive;

        public UDPSocket(byte[] buffer, AsyncCallback onreceive)
        {
            this.buffer = buffer;
            this.onreceive = onreceive;
        }

        public void Open()
        {
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

        public void Bind(IPEndPoint address)
        {
            socket.Bind(address);
            BeginReceive();
        }

        public void Connect(IPAddress address, int port)
        {
            socket.Connect(address, port);
            BeginReceive();
        }

        public void Disconnect()
        {
            socket.Dispose();
            socket = null;
        }

        public void Dispose()
        {
            socket.Dispose();
            socket = null;
        }

        private void BeginReceive() 
        {
            socket.BeginReceiveFrom(buffer, 0, buffer.Length, SocketFlags.None, ref endPoint, ReceiveCallback, null);
        }

        private void ReceiveCallback(IAsyncResult result)
        {
            onreceive.Invoke(result);
            socket.BeginReceiveFrom(buffer, 0, buffer.Length, SocketFlags.None, ref endPoint, ReceiveCallback, null);
        }

        public int EndReceiveFrom(IAsyncResult asyncResult, ref EndPoint endPoint) 
            => socket.EndReceiveFrom(asyncResult, ref endPoint);

        public void Send(byte[] data)
        {
            socket.BeginSend(data, 0, data.Length, SocketFlags.None, null, null);
        }

        public void SendTo(byte[] data, IPEndPoint destination)
        {
            socket.BeginSendTo(data, 0, data.Length, SocketFlags.None, destination, null, null);
        }
    }
}
