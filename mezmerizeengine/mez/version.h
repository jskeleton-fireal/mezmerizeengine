#pragma once
#include "settings.h"

//Modify this file PLEASE


//used to denote major versions
#define VERSION_MAJOR 0x002c
//used to denote minor versions. increment this when you want to break older net compatibility
#define VERSION_MINOR 0x0007
//used to denote build versions of the minor build. This isnt affected by anything. Use for whatever you want
#define VERSION_BUILD 0x10000000

#if 1
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__
#else
#define BUILD_DATE "hidden"
#define BUILD_TIME "hidden"
#endif

