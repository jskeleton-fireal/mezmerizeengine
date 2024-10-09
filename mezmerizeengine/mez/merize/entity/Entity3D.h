#pragma once
#include "mez/merize/entity/baseentity.h"
#include "mez/merize/data/entity_macros.h"
#include "mez/merize/merize.h"

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

	virtual void DeclareProperties(PropertiesVector* vector)
	{
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Position.x, sizeof(float), DataType::DT_Float, "Position_X"));
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Position.y,sizeof(float),DataType::DT_Float,"Position_Y"));
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Position.z,sizeof(float),DataType::DT_Float,"Position_Z"));
	
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Angles.m_angles[0], sizeof(float), DataType::DT_Float, "Angles_0"));
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Angles.m_angles[1], sizeof(float), DataType::DT_Float, "Angles_1"));
		vector->push_back(RawProperty(&m_ComponentContainer.FindTransform()->m_Transform.m_Angles.m_angles[2], sizeof(float), DataType::DT_Float, "Angles_2"));
	}
};

