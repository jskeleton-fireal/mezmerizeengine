#pragma once
#include "mez/merize/engine/baseengine.h"
#ifdef PROJECT_TESTING
class Engine_Testing : public BaseEngine
{
public:
	virtual const char* GetName() { return "testing"; }
	virtual void OnInitialized()
	{
#if 0
		RunCommand("entity_create testcube");
		RunCommand("entity_create controller_camera");
#else

		RunCommand("entity_create test_imp");
		RunCommand("entity_create controller_camera");
#endif
	}

	virtual void OnPreInitialized()
	{
		m_launchparameters.m_textmode = 0;
	}
};

#endif