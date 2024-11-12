#pragma once
#include "component.h"
#include "cmp_transform.h"
#include "cmp_renderable.h"


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

	void AddReserved(MezComponent* new_component, int slot);
	~ComponentContainer();
protected:
	typedef void (*componentfunc_t)(ComponentContainer*,MezComponent*);
	void ForeachComponent(componentfunc_t function);
public:
	//untested
	int size() { return RESERVED_C_COUNT + m_components.size(); }
	HComponent operator[](int i)
	{
		if (i < RESERVED_C_COUNT) return m_reserved[i];
		return m_components[i- RESERVED_C_COUNT];
	}
};