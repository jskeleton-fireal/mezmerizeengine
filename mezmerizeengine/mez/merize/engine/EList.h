#pragma once
//#include "hybridarray.h"
#include "mez/merize/merize.h"
#define MAX_ENTITIES 0x7ff
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
	bool IsFree() { return  !m_Entity; }
	bool IsNotFree() { return m_Entity; }
	bool IsGoodToUpdate()
	{
		return IsNotFree();
	}
};
class EList
{
	friend class BaseEngine;
	friend class MezBaseEntity;
public:
	EDef defs[MAX_ENTITIES];
	int def_highest=0;
protected:
	void update();
	bool add(MezBaseEntity* e);
	short m_internalidcounter = 0;
};

