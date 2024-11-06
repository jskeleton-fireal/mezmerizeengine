#pragma once
#include "mez/merize/entity/baseentity.h"
#include "mez/merize/data/entity_macros.h"
#include "mez/merize/merize.h"
#include <mez/merize/miscobjects/serializable/propdef/propdef_transform.h>

//an entity that lives in 3d space.

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

	virtual void DeclareProperties(class PropertyContainer* vector)
	{
		PropDef_Transform::create(vector, &m_ComponentContainer.FindTransform()->m_Transform);
	}
};

