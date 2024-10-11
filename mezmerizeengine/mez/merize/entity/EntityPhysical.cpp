#include "EntityPhysical.h"
#include "mez/merize/cmp/cmp_renderable.h"
#include "mez/merize/engine/baseengine.h"
#include "mez/merize/ren/rinterface/rinterface.h"

void MezEntityPhysical::SetModel(const char* name)
{
	MezComponent_Renderable* l_renderable= dynamic_cast<MezComponent_Renderable*>(m_ComponentContainer.FindRenderable());
	assert(l_renderable);
	l_renderable->m_Renderable->SetModel_Name(name);
}

int MezEntityPhysical::PrecacheModel(const char* name)
{
	MezComponent_Renderable* l_renderable = dynamic_cast<MezComponent_Renderable*>(m_ComponentContainer.FindRenderable());
	assert(l_renderable);
	return l_renderable->m_Renderable->PrecacheModel_Name(name);
}

void MezEntityPhysical::InitModel(const char* name)
{
	int precache_result = PrecacheModel(name);
	if (precache_result == -1) return;
	SetModel(name);
}

void MezEntityPhysical::SetModel(RModel_Base* raw_model)
{
	MezComponent_Renderable* l_renderable = dynamic_cast<MezComponent_Renderable*>(m_ComponentContainer.FindRenderable());
	assert(l_renderable);
	l_renderable->m_Renderable->SetModel(raw_model);
}

void MezEntityPhysical::initialize2()
{
	MezComponent_Renderable* l_renderable = dynamic_cast<MezComponent_Renderable*>(m_ComponentContainer.FindRenderable());
	l_renderable->m_Renderable->m_rInterface->RequestFeature(RINTERFACE_FEATURE_3D);
}

void MezEntityPhysical::SetLighting(bool f_lighting)
{
	return m_ComponentContainer.FindRenderable()->m_Renderable->m_rInterface->RequestFeature(f_lighting ? RINTERFACE_FEATURE_3D : RINTERFACE_FEATURE_3DLIGHTING);;
}
