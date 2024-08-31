#pragma once
#include "hybridarray.h"
#include "merize.h"
#define MAX_ENTITIES 0xff
//This must be big enough to hold MAX_ENTITIES
typedef short edef_tight_t;

class MezBaseEntity;

enum EDEF_STATUS
{
	EDEF_STATUS_READY = 0,
};

class EDef
{
public:
	MezBaseEntity* m_Entity=0;
	bool m_DeleteMe=0;
	//Sometimes entities may be created & spawned from seperate threads (ex: from the console)
	//so we need to make sure entities are initialized properly before doing stuff with them
	// 0 = ready
	s8 m_Status = -1;
	bool IsFree() { return  !m_Entity; }
	bool IsGoodToUpdate()
	{
		return !IsFree() && !m_Status;
	}
};
class EList
{
	friend class Engine;
	friend class MezBaseEntity;
public:
	EDef defs[MAX_ENTITIES];
	//hybridarray_dynamic_tight<EDef> defs = hybridarray_dynamic_tight<EDef>(MAX_ENTITIES);
protected:
	void update();
	bool add(MezBaseEntity* e);
	short m_internalidcounter = 0;
};

