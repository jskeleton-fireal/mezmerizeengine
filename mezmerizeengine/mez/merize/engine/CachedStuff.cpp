#include "CachedStuff.h"
#include "BaseEngine.h"
#include "mez/merize/staticdefs.h"
//okay so templates need to have all their stuff defined in the header file because of how they work
//but if its being created in the engine header file it cannot access the engine (it hasn't been defined yet)
//so im avoiding that by having this lameness
void CachedStuff_baseclassDONTUSETHISPLEASE::error_report(int code, const char* format, ...)
{
	const char* txttouse = 0;
	switch (code)
	{
	case 0:
		txttouse = "Failed to load %s %s and fallback %s %s could not be loaded";
		break;
	}
	char* txt = static_format(txttouse, prettyname(),format[0], prettyname(), format[1]);
	engine->fatalmsg(txt);
}
