#pragma once
#include "mez/merize/engine/baseengine.h"
#ifdef PROJECT_TESTING
class Engine_Testing : public BaseEngine
{
public:
	virtual const char* GetName() { return "testing"; }
	virtual void OnInitialized()
	{
		RunCommand("entity_create testcube");
		RunCommand("entity_create controller_camera");
	}
};

#endif