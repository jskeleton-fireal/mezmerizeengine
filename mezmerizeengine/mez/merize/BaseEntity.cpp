#include "BaseEntity.h"
#include "EList.h"
#include "Engine.h"
void MezBaseEntity::Spawn()
{
	assert(m_DefId == ENTITY_INVALID_DEFID);
	bool p = engine->elist.add(this);
	assert(p);
	Initialize();
	GetDef()->m_Status = EDEF_STATUS_READY;
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

MezBaseEntity* EHandle::get()
{
	MezBaseEntity* ref = engine->elist.defs[m_DefId].m_Entity;
	if (!ref || ref->m_InternalId != m_InternalId) return 0;
	return ref;
}
