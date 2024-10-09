#pragma once
#include "settings.h"

//include your own version system somewhere

#define MEZ_VERSION "v1.0_0"
#define MEZ_VERSION_NUMBERIC 0


#if 1
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__
#else
#define BUILD_DATE "hidden"
#define BUILD_TIME "hidden"
#endif

