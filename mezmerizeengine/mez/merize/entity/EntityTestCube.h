#pragma once
#include "EntityPhysical.h"
#include "../CachedStuff.h"
class MezEntityTestCube : public MezEntityPhysical
{
	virtual void Initialize()
	{
		MezEntityPhysical::Initialize();
		SetModel(MODEL_MISSING); //need null object
	}

	virtual void Update();
};

