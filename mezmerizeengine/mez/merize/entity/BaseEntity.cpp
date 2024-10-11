#include "BaseEntity.h"
#include "mez/merize/engine/EList.h"
#include "mez/merize/engine/BaseEngine.h"
void MezBaseEntity::Spawn()
{
	assert(m_DefId == ENTITY_INVALID_DEFID);
	bool p = engine->elist.add(this);
	assert(p);
	m_State = MEZENTSTATE_INITIALIZE_NEEDED;
}

EDef* MezBaseEntity::GetDef()
{
	assert(m_DefId >= 0 && m_DefId <= MAX_ENTITIES);
	return &engine->elist.defs[m_DefId];
}

void MezBaseEntity::Destroy()
{
	GetDef()->m_DeleteMe = 1;
}

EHandle MezBaseEntity::GetEHandle()
{
	return EHandle(this);
}

bool MezBaseEntity::HandleStates()
{
	switch (m_State)
	{
	case (MEZENTSTATE_INITIALIZE_NEEDED):
		m_State = MEZENTSTATE_INITIALIZING; Initialize(); m_State = MEZENTSTATE_READY; return 1;
	case MEZENTSTATE_READY:
		Update_Calls(); return 1;
	}
}

MezBaseEntity* MezBaseEntity::Find_Typeless(const char* f_classname)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (engine->elist.defs[i].IsFree()) continue;
		if (strcmp(f_classname, engine->elist.defs[i].m_Entity->GetClassname())) continue;
		return f_classname, engine->elist.defs[i].m_Entity;
	}
	return nullptr;
}

MezBaseEntity* EHandle::get()
{
	MezBaseEntity* ref = engine->elist.defs[m_DefId].m_Entity;
	if (!ref || ref->m_InternalId != m_InternalId) return 0;
	return ref;
}
