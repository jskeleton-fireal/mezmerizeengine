#pragma once
#include "component.h"
#include "../ren/MRenderable.h"

class MezComponent_Renderable : public MezComponent
{
public:
	COMPONENT_DEFINE(COMPONENT_INTERNAL_NAME_RENDERABLE, "Renderable");

	MRenderable* m_Renderable = new MRenderable();
	~MezComponent_Renderable() { delete m_Renderable; }
};

