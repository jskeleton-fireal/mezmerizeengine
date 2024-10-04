#include "EntityTestCube.h"
#include "../console/cmd.h"
#include "../ren/model_selfdef.h"
#include "../io/input.h"

ENTITY_LINK("testcube", MezEntityTestCube);

inline void MezEntityTestCube::Initialize()
{
	MezEntityPhysical::Initialize();
	RModel_SelfDef* testingmodel = new RModel_SelfDef();

	const float z = 0;
	const float bigpos = 0.9f;
	const float smalpos = -.8f;
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
	const float scale = 1.0f / 60.0f;
	float forward_move = Input::KeyFWAxis(MKC_W, MKC_S);
	float sideways_move = Input::KeyFWAxis(MKC_A, MKC_D);
	GetTransform()->m_Position.z += forward_move * scale;
	GetTransform()->m_Position.x += sideways_move * scale;

	if (Input::KeyPressed(MKC_B))
	{
		console_printf("%.2f,%.2f,%.2f\n", GetTransform()->m_Position.x, GetTransform()->m_Position.y, GetTransform()->m_Position.z );
	}
}

