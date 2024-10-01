#pragma once
#include "EntityPhysical.h"
#include "../CachedStuff.h"
class MezEntityTestCube : public MezEntityPhysical
{
	virtual void Initialize()
	{
		MezEntityPhysical::Initialize();
		InitModel("suzanne.obj");
	}

	virtual void Update();
};

