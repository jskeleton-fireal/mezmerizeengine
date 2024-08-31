#pragma once
#include "../merize.h"

//displaynames are disabled in release builds
#define COMPONENT_DISPLAYNAMES_ENABLED _DEBUG

#define COMPONENT_CREATEDISPLAYNAME(vDis) vDis

#if COMPONENT_DISPLAYNAMES_ENABLED
#define COMPONENT_SETDISPLAYNAME(vDisplayName) virtual const char* DisplayName() {return COMPONENT_CREATEDISPLAYNAME(vDisplayName);}
#else
#define COMPONENT_SETDISPLAYNAME(vDisplayName) //inherit from base
#endif
#define COMPONENT_DEFINE(vInternalName,vDisplayName) virtual const char* InternalName() {return vInternalName;} COMPONENT_SETDISPLAYNAME(vDisplayName)
class MezComponent
{
public:
	//keep these AS SMALL and CONCISE as possible. they are used for component searching
	virtual const char* InternalName() = 0;
	//used for debugging
	virtual const char* DisplayName() { return "?"; }
};

#define COMPONENT_INTERNAL_NAME_TRANSFORM "t"
#define COMPONENT_INTERNAL_NAME_RENDERABLE "r"

