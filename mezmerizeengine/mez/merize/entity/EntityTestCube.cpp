#include "EntityTestCube.h"
#include "../console/cmd.h"
#include "../ren/model_selfdef.h"

ENTITY_LINK("testcube", MezEntityTestCube);

inline void MezEntityTestCube::Initialize()
{
	MezEntityPhysical::Initialize();
	RModel_SelfDef* testingmodel = new RModel_SelfDef();

	const int z = 0;
	Vector* points = new Vector[3];
	points[0] = Vector(0,0,z);
	points[1] = Vector(0,0.9f,z);
	points[2] = Vector(0.9f,0,z);

	testingmodel->SelfDef_Create(points, 3);
	testingmodel->SelfDef_SetDrawmode(RModel_Mesh::DM_TriangleStrip);
	SetModel(testingmodel);
}

void MezEntityTestCube::Update()
{
	GetTransform()->m_Position.z = sinf(engine->time / 3.14f);
	GetTransform()->m_Position.x = cosf(engine->time / 3.14f);
	GetTransform()->m_Position.y = cosf(engine->time);
}
