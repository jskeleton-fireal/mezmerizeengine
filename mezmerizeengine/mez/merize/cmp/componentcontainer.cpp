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

void notify_added(ComponentContainer* container, MezComponent* newcomponent)
{
    for (int i = 0; i < container->RESERVED_C_COUNT; i++)
    {
        if (!container->m_reserved[i]) continue;
        container->m_reserved[i]->m_parent = container;
        container->m_reserved[i]->Container_ComponentWasAdded(newcomponent);
    }
    for (int i = 0; i < container->m_components.size(); i++)
    {
        container->m_components[i]->m_parent = container;
        container->m_components[i]->Container_ComponentWasAdded(newcomponent);
    }
    newcomponent->Initialize();
}

void ComponentContainer::AddComponent(MezComponent* newcomponent)
{
    newcomponent->m_parent = this;
    newcomponent->Initialize();
    notify_added(this, newcomponent);

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


void ComponentContainer::AddReserved(MezComponent* new_component, int slot)
{
    assert(slot < RESERVED_C_COUNT && slot > -1);
    new_component->m_parent = this;
    notify_added(this, new_component);
    m_reserved[slot] = new_component;
}

void ComponentContainer::ForeachComponent(componentfunc_t function)
{
}
