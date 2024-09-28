#pragma once
#include "../baseentity.h"
#include "../entity_macros.h"
#include "../merize.h"
#include "Entity3D.h"
//an entity that exists physically. has a 3d model and whatnot
class MezEntityPhysical : public MezEntity3DTransform
{
public:
	virtual void Initialize() {
		MezEntity3DTransform::Initialize();
		m_ComponentContainer.AddRenderable();
		
	}

	virtual void SetModel(const char* name);
};

