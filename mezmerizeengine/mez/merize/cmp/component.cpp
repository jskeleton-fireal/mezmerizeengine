#include "component.h"
#include "componentcontainer.h"
MezComponent* MezComponent::FindComponent(const char* f_internal_name)
{
    
    return m_parent->FindComponent(f_internal_name);
}

MezComponent_Transform* MezComponent::FindTransform()
{
    return m_parent->FindTransform();
}

MezComponent_Renderable* MezComponent::FindRenderable()
{
    return m_parent->FindRenderable();
}
