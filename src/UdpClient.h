#pragma once

class UdpClient
{
private:
	SOCKET sock;

public:
	UdpClient()
	{
		sock = INVALID_SOCKET;
	}

	~UdpClient()
	{
		Close();
	}

	bool CreateSocket()
	{
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		return sock != INVALID_SOCKET;
	}

	int SetClientToBroadcastMode()
	{
		int optval = 1;

		return setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval));
	}

	int Connect(ULONG address, u_short port)
	{
		SOCKADDR_IN dest{};
		dest.sin_family = AF_INET;
		dest.sin_port = htons(port);
		dest.sin_addr.S_un.S_addr = address;

		return connect(sock, (sockaddr*)&dest, sizeof(sockaddr_in));
	}

	int Send(const UCHAR* dgram, int bytes)
	{
		return send(sock, (const char*)dgram, bytes, 0);
	}

	void Close()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;
		}
	}
};
