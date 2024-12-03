#pragma once
#include <mez/settings.h>

//include your own version system somewhere

#define MEZ_VERSION "v0.4"
#define MEZ_VERSION_NUMERIC 4


#if 1
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__
#else
#define BUILD_DATE "hidden"
#define BUILD_TIME "hidden"
#endif

