#include "EntityTestCube.h"
#include "../console/cmd.h"
#include "../ren/model_selfdef.h"

ENTITY_LINK("testcube", MezEntityTestCube);

inline void MezEntityTestCube::Initialize()
{
	MezEntityPhysical::Initialize();
	RModel_SelfDef* testingmodel = new RModel_SelfDef();

	const float z = 0;
	const float bigpos = 0.9f;
	const float smalpos = 0.0f;
	Vector* points = new Vector[4];
	points[0] = Vector(smalpos,smalpos,z);
	points[1] = Vector(smalpos,bigpos,z);
	points[2] = Vector(bigpos,smalpos,z);
	points[3] = Vector(bigpos, bigpos,z);

	testingmodel->SelfDef_Create(points, 4);
	testingmodel->SelfDef_SetDrawmode(RModel_Mesh::DM_TriangleStrip);
	SetModel(testingmodel);
}

void MezEntityTestCube::Update()
{
	GetTransform()->m_Position.z = sinf(engine->time / 3.14f);
	GetTransform()->m_Position.x = cosf(engine->time / 3.14f);
	GetTransform()->m_Position.y = cosf(engine->time);
}

