#pragma once
#include "../baseentity.h"
#include "../entity_macros.h"
#include "../merize.h"

class MezEntity3DTransform : public MezBaseEntity
{
public:
	virtual void Initialize()
	{
		m_ComponentContainer.AddTransform();
	}


	Transform* GetTransform()
	{
		return &m_ComponentContainer.FindTransform()->m_Transform;
	}

	Vector GetPosition() { return GetTransform()->m_Position; }
};

