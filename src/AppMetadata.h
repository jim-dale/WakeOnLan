#pragma once

#ifndef BUILDNUM
#define BUILDNUM NotSet
#endif

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

#define VERSION(x) "1.0.0-" STRINGIFY(x)

static const char* ProgramName = "WakeOnLan";
static const char* ProgramVersion = VERSION(BUILDNUM);

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
