#pragma once

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

// test if a defined macro has no value
#define __DO_EXPAND(x) x ## 1
#define __EXPAND(x) __DO_EXPAND(x)
#define MACRO_HAS_NO_VALUE(x) (__EXPAND(x) == 1)

#define SHORTGITHASHLEN 8

#define VERSION "1.0.1"

#pragma warning(push)
#pragma warning(disable:4003)
#if !defined(BUILDNUM)
#define BUILDNUM NotSet
#elif MACRO_HAS_NO_VALUE(BUILDNUM)
#undef BUILDNUM
#define BUILDNUM NotSet
#endif
#pragma warning(pop)

static const char * ProgramName = "WakeOnLan";
static const char * ProgramVersion = VERSION;
static const char * GitHash = STRINGIFY(BUILDNUM);

#if defined(_DEBUG)
static const char * ProgramConfig = "Debug";
#elif defined(NDEBUG)
static const char * ProgramConfig = "Release";
#else
static const char * ProgramConfig = "Undefined";
#endif
#if defined(_M_IX86)
static const char * ProgramPlatform = "x86";
#elif defined(_M_X64)
static const char * ProgramPlatform = "x64";
#else
static const char * ProgramPlatform = "Undefined";
#endif
