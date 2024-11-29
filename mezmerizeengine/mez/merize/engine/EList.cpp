#include "EList.h"
#include "mez/merize/entity/BaseEntity.h"
#include <mez/merize/helpers/quikrng.h>
//#define MAX_ENTS_CHECK defs.size()
#define MAX_ENTS_CHECK def_highest + 1

//Unused
void find_highest_2(EList* r,int range = MAX_ENTITIES)
{
	int c = 0;
	for (int i = 0; i < range; i++)
	{
		if (r->defs[i].IsNotFree())
		{
			//dont need to check anything else. its always gonna be higher number than the last
			c = i;
		}
	}
	r->def_highest = c;
}

void EList::update()
{
	int numtodelete = 0;
	int highest_recorded = -1;
	for (int i = 0; i < MAX_ENTS_CHECK; i++)
	{
		if (!defs[i].IsGoodToUpdate()) continue;
		MezBaseEntity* entity = defs[i].m_Entity;
		assert(entity->HandleStates());
		if (entity->m_DeleteMe)
			numtodelete++;
		else
			highest_recorded = i;
	}

	if (numtodelete)
	{
		for (int i = 0; i < MAX_ENTS_CHECK; i++)
		{
			if (defs[i].IsFree()) continue;
			MezBaseEntity* entity = defs[i].m_Entity;
			if (entity->m_DeleteMe)
			{
				delete entity;
				defs[i].m_Entity = 0;
			}
		}
		def_highest = highest_recorded;
	}
}

bool EList::add(MezBaseEntity* e)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (!defs[i].IsFree()) continue;
		defs[i] = EDef();
		defs[i].m_Entity = e;
		e->m_DefId = i;
		e->m_InternalId = quikrng16(m_internalidcounter);
		m_internalidcounter++;
		if (i >= def_highest)
		{
			def_highest = i;
		}
		return 1;
	}

	return 0;
}
