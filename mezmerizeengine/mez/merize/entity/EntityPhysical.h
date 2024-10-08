#pragma once
#include "mez/merize/entity/baseentity.h"
#include "mez/merize/data/entity_macros.h"
#include "mez/merize/merize.h"
#include "mez/merize/entity/Entity3D.h"
//an entity that exists physically. has a 3d model and whatnot
class RModel_Base;
class MezEntityPhysical : public MezEntity3DTransform
{
public:
	virtual void Initialize() {
		MezEntity3DTransform::Initialize();
		m_ComponentContainer.AddRenderable();
		
	}

	virtual void SetModel(const char* name);
	virtual int PrecacheModel(const char* name);
	//precache + set. For Initialize() only! please!
	virtual void InitModel(const char* name);
	//for dorks
	virtual void SetModel(RModel_Base* raw_model);
};

