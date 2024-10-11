#include "cmp_renderable.h"
#include "cmp_transform.h"
#include "../ren/rinterface/rinterface.h"
#include "componentcontainer.h"

void MezComponent_Renderable::Initialize()
{
	MezComponent_Transform* transform = m_parent->FindTransform();
	m_Renderable->m_rInterface->m_transform = &transform->m_Transform;
}

void MezComponent_Renderable::RequestFeature(rinterface_feature_t f_feature)
{
	m_Renderable->m_rInterface->RequestFeature(f_feature);
}
