#pragma once
#include "component.h"
#include "../ren/MRenderable.h"

class MezComponent_Renderable : public MezComponent
{
public:
	COMPONENT_DEFINE(COMPONENT_INTERNAL_NAME_RENDERABLE, "Renderable");

	unique_ptr<MRenderable> m_Renderable = make_unique<MRenderable>(MRenderable());
};

