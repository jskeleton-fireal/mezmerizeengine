#include "EList.h"
#include "BaseEntity.h"

//#define MAX_ENTS_CHECK defs.size()
#define MAX_ENTS_CHECK MAX_ENTITIES

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

		return 1;
	}

	return 0;
}
