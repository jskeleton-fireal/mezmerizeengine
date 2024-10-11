#pragma once
#include "mez/merize/entity/EntityPhysical.h"
#include "mez/merize/engine/CachedStuff.h"
class TstEntityTestCube : public MezEntityPhysical
{
	DECLARE_ENTITY(TstEntityTestCube);
	virtual void Initialize();

	virtual void Update();

};

