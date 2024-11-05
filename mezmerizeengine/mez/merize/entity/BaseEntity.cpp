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
	//featurereq: this MIGHT be faster if you have a functionptr set or something.. so if its ready it'll be updatecalls and if its not its this func. maybe thats faster
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
		//return f_classname, engine->elist.defs[i].m_Entity; //What the hell?
		return engine->elist.defs[i].m_Entity;
	}
	return nullptr;
}

