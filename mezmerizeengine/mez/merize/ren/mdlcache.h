#pragma once
class RModel_Base;
class RModel;
#include "mez/merize/engine/cachedstuff.h"
#include "model.h"

class CachedStuff_RModels : public CachedStuff<RModel_Base>
{
public:
	CachedStuff_RModels()
	{
		
	}
	virtual void CreateDefaults()
	{
		Upload(Fallback(), RModel::LoadModelFromFile(Fallback(),1));
	}
	virtual const char* Fallback() { return "null"; }
	virtual const char* prettyname() { return "model"; }
};