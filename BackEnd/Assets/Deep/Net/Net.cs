using System;
using System.Net;

namespace Deep.Net {
    public static class Net {
        public delegate void onConnect(EndPoint endpoint);
        public delegate void onAccept(EndPoint endpoint);
        public delegate void onReceive(ArraySegment<byte> buffer, EndPoint endpoint);
        public delegate void onDisconnect(EndPoint endpoint);
    }
}
