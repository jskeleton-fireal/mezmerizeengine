#include "EHandle.h"
#include "mez/merize/engine/EList.h"
#include "mez/merize/engine/BaseEngine.h"

MezBaseEntity* EHandle::get()
{
	MezBaseEntity* ref = engine->elist.defs[m_DefId].m_Entity;
	if (!ref || ref->m_InternalId != m_InternalId) return 0;
	return ref;
}

EHandle::EHandle(MezBaseEntity* ref) { m_DefId = ref->m_DefId; m_InternalId = ref->m_InternalId; }

bool EHandle::good() { return ((m_DefId)+1) && get() && ptr_matches(); }

//hopefully this is faster than inversion

bool EHandle::bad() { return (!good()); }

//need its own body for perf.. but this will do for now

EHandle::operator bool() { return good(); }

//private cause it expects get() to be valid

bool EHandle::ptr_matches()
{
	return get()->m_InternalId == m_InternalId && get()->m_DefId == m_DefId;
}
