#pragma once
#include "component.h"
#include "cmp_transform.h"
#include "cmp_renderable.h"


//todo: THIS DOES NOT FREE COMPONENTS AT THE MOMEMTN PLEASE FIX THIS GOD 

class ComponentContainer
{
public:
	//some components used internally by the engine are reserved for quick access
	enum
	{
		RESERVED_TRANSFORM,
		RESERVED_RENDERABLE,
		RESERVED_C_COUNT,
	};
	typedef MezComponent* HComponent;

public:
	HComponent m_reserved[RESERVED_C_COUNT];
	std::vector<HComponent> m_components;
public:
	//avoid using this for reserveds
	void AddComponent(MezComponent* new_component);

	void AddTransform();
	void AddRenderable();

	possibly_null(MezComponent*) FindComponent(const char* internal_name);
	inline possibly_null(MezComponent_Transform*) FindTransform() { return dynamic_cast<MezComponent_Transform*>(m_reserved[RESERVED_TRANSFORM]); }
	inline possibly_null(MezComponent_Renderable*) FindRenderable() { return dynamic_cast<MezComponent_Renderable*>(m_reserved[RESERVED_RENDERABLE]); }

	inline void AddReserved(MezComponent* new_component, int slot)
	{
		assert(slot < RESERVED_C_COUNT && slot > -1);
		m_reserved[slot] = new_component;
	}

};