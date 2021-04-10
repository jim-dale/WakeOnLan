#pragma once

#pragma pack (push, 1)

struct MacAddress
{
	UCHAR bytes[MAC_ADDR_LEN];

	/// <summary>
	/// Returns whether the MAC address is empty.
	/// </summary>
	/// <returns></returns>
	bool IsEmpty()
	{
		auto v = bytes[0] | bytes[1] | bytes[2] | bytes[3] | bytes[4] | bytes[5];

		return v == 0;
	}

	/// <summary>
	/// Convert a string representation of the MAC address to 6 binary bytes.
	/// </summary>
	/// <param name="mac">MAC address string.</param>
	/// <param name="maclen">length of the mac address string.</param>
	/// <param name="result">The MAC address as a byte array</param>
	/// <returns></returns>
	static MacAddress ToBytes(const char* mac)
	{
		return ToBytes(mac, strlen(mac));
	}

	static MacAddress ToBytes(const char* mac, size_t maclen)
	{
		MacAddress result{};
		int num_fields = 0;

		if (maclen == 12)
		{	// No separator
			num_fields = sscanf(mac, "%hhx%hhx%hhx%hhx%hhx%hhx", &result.bytes[0], &result.bytes[1], &result.bytes[2], &result.bytes[3], &result.bytes[4], &result.bytes[5]);
		}
		else if (maclen == 17)
		{	// dash or colon separator
			if (mac[2] == '-')
			{
				num_fields = sscanf(mac, "%hhx-%hhx-%hhx-%hhx-%hhx-%hhx", &result.bytes[0], &result.bytes[1], &result.bytes[2], &result.bytes[3], &result.bytes[4], &result.bytes[5]);
			}
			else if (mac[2] == ':')
			{
				num_fields = sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &result.bytes[0], &result.bytes[1], &result.bytes[2], &result.bytes[3], &result.bytes[4], &result.bytes[5]);
			}
		}
		if (num_fields != 6)
		{
			ZeroMemory(&result, sizeof(result));
		}

		return result;
	}
};

#pragma pack (pop)
