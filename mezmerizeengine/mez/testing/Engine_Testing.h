#pragma once
#include "mez/merize/engine/baseengine.h"

class Engine_Testing : public BaseEngine
{
public:
	virtual const char* GetName() { return "testing"; }
	virtual void OnInitialized()
	{
		RunCommand("entity_create testcube");
	}
};

