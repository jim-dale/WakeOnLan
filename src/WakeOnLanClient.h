#pragma once

class WakeOnLanClient
{
public:
	static bool Send(const MacAddress& address, USHORT port)
	{
		bool result = false;

		auto client = UdpClient();

		if (client.CreateSocket() == false)
		{
			WinsockHelper::PrintLastError("Failed to open socket: %s\n");
		}
		else
		{
			if (client.SetClientToBroadcastMode() == SOCKET_ERROR)
			{
				WinsockHelper::PrintLastError("Failed to set socket to broadcast mode: %s\n");
			}
			else
			{
				if (client.Connect(INADDR_BROADCAST, port) == SOCKET_ERROR)
				{
					WinsockHelper::PrintLastError("Failed to connect to the broadcast address: %s\n");
				}
				else
				{
					auto datagram = WolPacket::Build(address);

					auto res = client.Send(datagram.sync, sizeof(datagram));
					if (res == sizeof(datagram))
					{
						result = true;
					}
					if (res == SOCKET_ERROR)
					{
						WinsockHelper::PrintLastError("Failed to send the Wake On LAN packet: %s\n");
					}
				}
			}
		}

		return result;
	}
};
