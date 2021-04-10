#pragma once

class WinsockHelper
{
public:
	static int Initialise()
	{
		WSADATA wsaData;

		return WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	static void Uninitialise()
	{
		WSACleanup();
	}

	static void PrintLastError(const char* fmt)
	{
		int error = WSAGetLastError();
		char buffer[512];

		strerror_s(buffer, error);

		fprintf(stderr, fmt, buffer);
	}
};
