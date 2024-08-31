#pragma once
#include "component.h"
#include "../transform.h"
class MezComponent_Transform : public MezComponent
{
public:
	COMPONENT_DEFINE(COMPONENT_INTERNAL_NAME_TRANSFORM, "Transform");
	Transform m_Transform = Transform();
};

