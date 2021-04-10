#pragma once

struct AppArguments
{
	bool showHelp;
	bool showVersion;

	MacAddress macAddress;
	USHORT port;

	std::string errorMessage;
};
