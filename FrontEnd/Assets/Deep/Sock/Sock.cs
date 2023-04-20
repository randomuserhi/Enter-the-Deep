using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Net;

using UnityEngine; // Temporary for logging

namespace Deep.Sock
{
    public class Socket
    {
        private byte[] buffer;
        private EndPoint endPoint = new IPEndPoint(IPAddress.Any, 0);
        private System.Net.Sockets.Socket socket = null;

        public Socket(int bufferSize) 
        {
            buffer = new byte[bufferSize];
        }

        public void Open()
        {
            if (socket != null) socket.Dispose();
            socket = new System.Net.Sockets.Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
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
            int numBytes = socket.EndReceiveFrom(result, ref endPoint);
            socket.BeginReceiveFrom(buffer, 0, buffer.Length, SocketFlags.None, ref endPoint, ReceiveCallback, null);
            
            Debug.Log($"Recieved {numBytes} bytes.");
        }

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
