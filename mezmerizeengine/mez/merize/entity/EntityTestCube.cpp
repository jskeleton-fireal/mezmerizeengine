#include "EntityTestCube.h"
#include "../console/cmd.h"
#include "../ren/model_selfdef.h"
#include "../io/input.h"

ENTITY_LINK("testcube", MezEntityTestCube);

inline void MezEntityTestCube::Initialize()
{
	MezEntityPhysical::Initialize();
#if 0
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
#else
	InitModel("testcube.obj");
#endif
}

mezstring_t serialized;
void MezEntityTestCube::Update()
{
	const float scale = engine->time_delta * 3;
	float forward_move = Input::KeyFWAxis(MKC_W, MKC_S);
	float sideways_move = Input::KeyFWAxis(MKC_A, MKC_D);
	GetTransform()->m_Position.z += forward_move * scale * 20;
	GetTransform()->m_Position.x += sideways_move * scale * 20;
	GetTransform()->m_Angles.m_angles[0] += Input::KeyHeld(MKC_R) * scale * 6;
	GetTransform()->m_Angles.m_angles[1] += Input::KeyHeld(MKC_T) * scale * 6;
	GetTransform()->m_Angles.m_angles[2] += Input::KeyHeld(MKC_Y) * scale * 6;

	if (Input::KeyPressed(MKC_B))
	{
		console_printf("%.2f,%.2f,%.2f\n", GetTransform()->m_Position.x, GetTransform()->m_Position.y, GetTransform()->m_Position.z );
	}
	if (Input::KeyPressed(MKC_V))
	{
		GetTransform()->m_Angles.m_angles[0] = 0;
		GetTransform()->m_Angles.m_angles[1] = 0;
		GetTransform()->m_Angles.m_angles[2] = 0;
	}	
	if (Input::KeyPressed(MKC_N))
	{
		console_printf("fps = %.2f\n",1.0f / engine->time_delta);
	}
	if (Input::KeyPressed(MKC_K))
	{
		mezstring_t ser = Serialize();
		console_printf("\n ------ \n %s\n -----\n\n", ser);
		serialized.clone(&ser);
	}
	if (Input::KeyPressed(MKC_L))
	{
		bool workd = DeSerialize(serialized);
		console_printf("YOU SHOULD SEE 1 BELOW\n%x", workd);
	}
}

