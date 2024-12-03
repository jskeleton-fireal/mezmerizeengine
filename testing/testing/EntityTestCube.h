#pragma once
#include "mez/merize/entity/EntityPhysical.h"
#include "mez/merize/engine/CachedStuff.h"
class TstEntityTestCube_1 : public MezEntityPhysical
{
	public:
	DECLARE_ENTITY(TstEntityTestCube_1);
	public:
	virtual void Initialize();
	virtual void Update();

};
class TstEntityTestCube_2 : public TstEntityTestCube_1
{
public:
	DECLARE_ENTITY(TstEntityTestCube_2);
public:

	virtual void Initialize();
	virtual void Update();
	
};


