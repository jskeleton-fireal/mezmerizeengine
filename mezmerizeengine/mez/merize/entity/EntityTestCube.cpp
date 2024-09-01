#include "EntityTestCube.h"
#include "../console/cmd.h"

ENTITY_LINK("testcube", MezEntityTestCube);

void MezEntityTestCube::Update()
{
	const char* model_name = m_ComponentContainer.FindRenderable()->m_Renderable->m_model->m_name.c_str();
	console_printf("%s\n", model_name);
}
