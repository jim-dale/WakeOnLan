#pragma once

#pragma pack (push, 1)

struct WolPacket
{
	UCHAR sync[MAC_ADDR_LEN];
	UCHAR target[MAC_COUNT * MAC_ADDR_LEN];

	/// <summary>
	/// Builds a Wake On LAN magic packet for the specified MAC address.
	/// </summary>
	/// <param name="value">The MAC address to generate the magic packet for.</param>
	/// <returns>The magic packet.</returns>
	static WolPacket Build(const MacAddress& value)
	{
		WolPacket result;
		ZeroMemory(&result, sizeof(result));

		// Build the Synchronization Stream (6 bytes of 0xFF)
		for (int i = 0; i < MAC_ADDR_LEN; i++)
		{
			result.sync[i] = 0xff;
		}

		// Now repeat the Target MAC 16 times
		for (int i = 0; i < MAC_COUNT; i++)
		{
			for (int j = 0; j < MAC_ADDR_LEN; j++)
			{
				result.target[(i * MAC_ADDR_LEN) + j] = value.bytes[j];
			}
		}

		return result;
	}
};

#pragma pack (pop)
