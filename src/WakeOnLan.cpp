#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#include <string>
#include <stdexcept>

#include <ws2tcpip.h>

#include "AppMetadata.h"
#include "Definitions.h"
#include "MacAddress.h"
#include "WolPacket.h"
#include "UdpClient.h"
#include "WinsockHelper.h"
#include "WakeOnLanClient.h"
#include "AppArguments.h"
#include "CommandLine.h"

#pragma comment (lib, "Ws2_32.lib")


int main(int argc, char** argv)
{
	int result = EXIT_FAILURE;

	auto args = CommandLine::ParseCommandLine(argc, argv);
	if (args.showVersion)
	{
		CommandLine::ShowVersion();
	}
	else if (args.errorMessage.empty() == false)
	{
		CommandLine::ShowHelp();
		CommandLine::ShowError(args);
	}
	else if (args.showHelp)
	{
		CommandLine::ShowHelp();
	}
	else
	{
		if (WinsockHelper::Initialise() != 0)
		{
			fprintf(stderr, "WSAStartup failed with error: %d\n", result);
		}
		else
		{
			if (WakeOnLanClient::Send(args.macAddress, args.port))
			{
				result = EXIT_SUCCESS;
			}

			WinsockHelper::Uninitialise();
		}
	}

	return result;
}
