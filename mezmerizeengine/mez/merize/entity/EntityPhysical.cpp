#include "EntityPhysical.h"
#include "../cmp/cmp_renderable.h"

void MezEntityPhysical::SetModel(const char* name)
{
	MezComponent_Renderable* l_renderable= dynamic_cast<MezComponent_Renderable*>(m_ComponentContainer.FindRenderable());
	assert(l_renderable);
	l_renderable->m_Renderable->SetModel_Name(name);
}
