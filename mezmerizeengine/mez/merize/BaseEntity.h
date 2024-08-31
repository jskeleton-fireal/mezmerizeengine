#pragma once
#include "merize.h"
#include "EList.h"
#include "transform.h"
#include "cmp/component.h"
#include "cmp/componentcontainer.h"
#include "entityprivate/efactory.h"
#define ENTITY_INVALID_DEFID -1
class EDef;
class MezBaseEntity;
class EHandle;




enum
{
	LIFESTATE_DEAD,
	LIFESTATE_ALIVE,
};

class MezBaseEntity
{
public:
	//id in the edef. gets updated on Spawn()
	int m_DefId = ENTITY_INVALID_DEFID;
	//hidden id to prevent ehandle clashing. gets updated on Spawn()
	short m_InternalId = -1;

	ComponentContainer m_ComponentContainer;

public:
	void Spawn();
	EDef* GetDef();
	void Destroy();
	EHandle GetEHandle();
	template <class T>
	T* Cast() { return dynamic_cast<T*>(this); }
public:
	virtual void Update() {}
	virtual void Pre_Update() {}
	virtual void Post_Update() {}
public:
	virtual void Initialize() {}
};

//Use EHandles in place of Entity pointers Please

class EHandle
{
	//todo: make some operators
public:
	edef_tight_t m_DefId = ENTITY_INVALID_DEFID;
	short m_InternalId = -1;
	MezBaseEntity* get();
	template <class T>
	T* get() { return dynamic_cast<T*>(get()); }
	EHandle() {}
	EHandle(MezBaseEntity* ref) { m_DefId = ref->m_DefId; m_InternalId = ref->m_InternalId; }
};
