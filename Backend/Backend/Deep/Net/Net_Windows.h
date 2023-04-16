#pragma once

namespace Deep
{
	int InitializeSockets();
	int ShutdownSockets();
	Deep_Inline int GetWSAError()
	{
		return WSAGetLastError();
	}
}