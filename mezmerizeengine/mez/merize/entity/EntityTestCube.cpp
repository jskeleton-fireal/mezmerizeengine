#include "EntityTestCube.h"
#include "../console/cmd.h"

ENTITY_LINK("testcube", MezEntityTestCube);

void MezEntityTestCube::Update()
{
	GetTransform()->m_Position.z = sinf(engine->time / 3.14f);
	GetTransform()->m_Position.x = cosf(engine->time / 3.14f);
	GetTransform()->m_Position.y = cosf(engine->time);
}
