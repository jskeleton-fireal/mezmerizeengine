#include "componentcontainer.h"
#include "cmp_transform.h"

possibly_null(MezComponent*) ComponentContainer::FindComponent(const char* internal_name)
{
    for (int i = 0; i < m_components.size(); i++)
    {
        if (!strcmp(m_components[i]->InternalName(), internal_name))
        return m_components[i];
    }
    //alright.. check reserved..
    for (int i = 0; i < RESERVED_C_COUNT; i++)
    {
        //reserveds dont need to exist
        if (!m_reserved[i]) continue;
        if (!strcmp(m_reserved[i]->InternalName(), internal_name))
            return m_reserved[i];
    }
    return 0;
}

void ComponentContainer::AddComponent(MezComponent* newcomponent)
{
    m_components.push_back(newcomponent);
}

void ComponentContainer::AddTransform()
{
    assert(!FindTransform());
    AddReserved(new MezComponent_Transform(), RESERVED_TRANSFORM);
}

void ComponentContainer::AddRenderable()
{
    assert(!FindRenderable());
    AddReserved(new MezComponent_Renderable(), RESERVED_RENDERABLE);
}
