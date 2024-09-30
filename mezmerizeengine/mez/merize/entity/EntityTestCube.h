#pragma once
#include "EntityPhysical.h"
#include "../CachedStuff.h"
class MezEntityTestCube : public MezEntityPhysical
{
	virtual void Initialize()
	{
		MezEntityPhysical::Initialize();
		InitModel("suzanne.obj"); //need null object
	}

	virtual void Update();
};

