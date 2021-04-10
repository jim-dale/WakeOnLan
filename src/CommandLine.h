#pragma once

class CommandLine
{
private:
	enum class ParserState
	{
		ExpectOptionOrMacAddress
		, ExpectPortNumber
	};

public:
	static AppArguments ParseCommandLine(size_t argc, char const* const* argv)
	{
		AppArguments result{};
		result.port = WOL_PORT;
		result.showHelp = (argc == 1);

		ParserState state = ParserState::ExpectOptionOrMacAddress;

		// Skip the first argument because by convention, argv[0] is the command with which the program is invoked.
		for (size_t i = 1; i < argc; i++)
		{
			std::string arg(argv[i]);
			size_t length = arg.length();

			switch (state)
			{
			case ParserState::ExpectOptionOrMacAddress:
				if (length > 1 && (arg[0] == '-' || arg[0] == '/'))
				{
					state = ProcessOption(result, &arg[1]);
				}
				else
				{
					ProcessMacAddress(result, arg);
				}
				break;
			case ParserState::ExpectPortNumber:
				ProcessPortNumber(result, arg);
				state = ParserState::ExpectOptionOrMacAddress;
				break;
			default:
				break;
			}
		}

		if (result.errorMessage.empty() == true && result.macAddress.IsEmpty())
		{
			result.showHelp = true;
			result.errorMessage = std::string("The MAC address of the target computer must be specified.");
		}

		return result;
	}

	static void ShowHelp()
	{
		CommandLine::ShowVersion();

		printf("Broadcasts a Wake On LAN packet on the local network to wake a computer from sleep.\n\n");

		printf("Usage: %s [-?] [-v] [-p port_number] MAC_Address\n\n", ProgramName);

		printf("  -?           Display this help information.\n");
		printf("  -v           Display version information.\n");
		printf("  -p           The target port number to send the WOL packet to (default: 9).\n");
		printf("  MAC_Address  MAC address of the computer to wake up.\n");
		printf("               Supported format is six groups of two hexadecimal digits with an optional dash or colon separating the digit pairs.\n");
		printf("               For example: 0123456789AB or 01-23-45-67-89-AB or 01:23:45:67:89:AB\n\n");
	}

	static void ShowVersion()
	{
		printf("%s %s-%s-%s\n\n", ProgramName, ProgramVersion, ProgramPlatform, ProgramConfig);
	}

	static void ShowError(const AppArguments& args)
	{
		fprintf(stderr, "%s\n", args.errorMessage.c_str());
	}

private:
	static ParserState ProcessOption(AppArguments& args, const char* arg)
	{
		ParserState result = ParserState::ExpectOptionOrMacAddress;

		if (_stricmp("?", arg) == 0)
		{
			args.showHelp = true;
		}
		else if (_stricmp("v", arg) == 0)
		{
			args.showVersion = true;
		}
		else if (_stricmp("p", arg) == 0)
		{
			result = ParserState::ExpectPortNumber;
		}
		else
		{
			args.showHelp = true;
			args.errorMessage = std::string("Parameter format not correct - '") + std::string(arg) + std::string("'.");
		}
		return result;
	}

	static void ProcessMacAddress(AppArguments& args, const std::string& arg)
	{
		args.macAddress = MacAddress::ToBytes(arg.c_str());
		if (args.macAddress.IsEmpty())
		{
			args.showHelp = true;
			args.errorMessage = std::string("The MAC address is not valid.");
		}
	}

	static void ProcessPortNumber(AppArguments& args, const std::string& arg)
	{
		int port = -1;

		try
		{
			port = std::stoi(arg);
		}
		catch (const std::exception&)
		{
		}

		if (port >= 0 && port <= 0xffff)
		{
			args.port = port;
		}
		else
		{
			args.showHelp = true;
			args.errorMessage = std::string("The port number is not valid.");
		}
	}
};
