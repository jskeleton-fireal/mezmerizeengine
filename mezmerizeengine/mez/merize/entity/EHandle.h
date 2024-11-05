#pragma once
#include "BaseEntity.h"

//Use EHandles in place of Entity pointers Please

class EHandle
{
	//todo: make some operators
public:
	edef_tight_t m_DefId = ENTITY_INVALID_DEFID;
	signed short m_InternalId = -1;
	MezBaseEntity* get();
	template <class T>
	T* get() { return dynamic_cast<T*>(get()); }
	EHandle() {}
	EHandle(MezBaseEntity* ref);
	bool good(); //hopefully this is faster than inversion
	bool bad(); //need its own body for perf.. but this will do for now
	operator bool();

private:
	//private cause it expects get() to be valid
	bool ptr_matches();
	void refcopy(MezBaseEntity* ptr)
	{
		m_DefId = ptr->m_DefId;
		m_InternalId = ptr->m_InternalId;
	}
};

//todo: need some stuff to auto dynamic cast stuff stuff stuff do stuff
template <class T>
class EHandle_Typed : public EHandle
{
public:
	T* get() { return dynamic_cast<T*>(get()); }
};

