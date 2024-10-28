#include "EList.h"
#include "mez/merize/entity/BaseEntity.h"

//#define MAX_ENTS_CHECK defs.size()
#define MAX_ENTS_CHECK def_highest + 1

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
	for (int i = 0; i < MAX_ENTS_CHECK; i++)
	{
		if (!defs[i].IsGoodToUpdate()) continue;
		MezBaseEntity* entity = defs[i].m_Entity;
		assert(entity->HandleStates());
		if (defs[i].m_DeleteMe) numtodelete++;
	}

	if (numtodelete)
	{
		for (int i = 0; i < MAX_ENTS_CHECK; i++)
		{
			if (defs[i].IsFree()) continue;
			if (defs[i].m_DeleteMe)
			{
				delete defs[i].m_Entity;
				defs[i].m_Entity = 0;
				if (i >= def_highest)
				{
					find_highest_2(this,MAX_ENTS_CHECK);
				}
			}
		}
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
		e->m_InternalId = m_internalidcounter;
		m_internalidcounter++;
		if (i >= def_highest)
		{
			def_highest = i;
		}
		return 1;
	}

	return 0;
}
