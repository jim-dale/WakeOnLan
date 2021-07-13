#pragma once

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

#define SHORTGITHASHLEN 8
#define CHECK_SOURCEVERSION NOTSET
static const char* Check_SourceVersion = STRINGIFY(-CHECK_SOURCEVERSION-);

static const char* ProgramName = "WakeOnLan";
static const char* ProgramVersion = "1.0.1";
static const char* GitHash = STRINGIFY(BUILD_SOURCEVERSION-CHECK_SOURCEVERSION-);

#if defined(_DEBUG)
static const char* ProgramConfig = "Debug";
#elif defined(NDEBUG)
static const char* ProgramConfig = "Release";
#else
static const char* ProgramConfig = "Undefined";
#endif
#if defined(_M_IX86)
static const char* ProgramPlatform = "x86";
#elif defined(_M_X64)
static const char* ProgramPlatform = "x64";
#else
static const char* ProgramPlatform = "Undefined";
#endif
