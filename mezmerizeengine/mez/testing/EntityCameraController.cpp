#include "EntityCameraController.h"
#include <mez/merize/merize.h>
#include <mez/merize/engine/BaseEngine.h>
#include <mez/merize/io/input.h>
#include <mez/merize/console/cmd.h>
ENTITY_LINK(PROJECT_TESTING, "controller_camera", TstEntityCameraController);

void TstEntityCameraController::Initialize()
{
	MezEntity3DTransform::Initialize();
	engine->rendersys.m_camera.change(&m_Camera, false);
	MezEntity3DTransform* target = MezBaseEntity::Find<MezEntity3DTransform>("testcube");
	if (target)
	{
		m_Target = target->GetEHandle();
	}
}
ConsoleVariableFloat cv_dis("dis", 0, 10.0f);
ConsoleVariableBool cv_x("x", 0, 0);

void TstEntityCameraController::Update()
{
	const float scale = (Input::KeyHeld(MKC_Q) ? 30 : 0.2f);
	if (cv_x) {
	GetTransform()->m_Position.x = cosf(engine->time * scale) * cv_dis;
	GetTransform()->m_Position.z = sinf(engine->time * scale) * cv_dis;
	}
	else
	{
		float x = Input::KeyFWAxis(MKC_I, MKC_K);
		float z = Input::KeyFWAxis(MKC_J, MKC_L);
		float p = Input::KeyFWAxis(MKC_Y, MKC_H);
		GetTransform()->m_Position += GetTransform()->m_Angles.ForwardVector() * x * engine->time_delta;
		GetTransform()->m_Position += GetTransform()->m_Angles.RightVector_3D() * z * engine->time_delta;
		GetTransform()->m_Angles.m_angles[0] += p * engine->time_delta;

		if (Input::KeyHeld(MKC_U))
		{
			GetTransform()->m_Position += GetTransform()->m_Angles.UpVector();
		}
	}
	//GetTransform()->m_Position.x = (cosf(engine->time * scale)) * 8;
	//GetTransform()->m_Position.y = sinf(engine->time * scale * 0.05f) * 8;
	
	if (m_Target)
	{
		Vector* pos = &m_Target.get()->m_ComponentContainer.FindTransform()->m_Transform.m_Position;
		//GetTransform()->LookAt((*pos));
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			if (i == this->m_DefId) continue;
			if (engine->elist.defs[i].IsNotFree())
			{
				m_Target = engine->elist.defs[i].m_Entity->GetEHandle();
			}
		}
	}
	m_Camera.m_transform = *GetTransform();

	
	if (Input::KeyPressed(MKC_N))
	{
		console_printf("angle %.2f,%.2f,%.2f\n", GetTransform()->m_Angles.m_angles[0], GetTransform()->m_Angles.m_angles[1], GetTransform()->m_Angles.m_angles[2]);
	}	
	if (Input::KeyPressed(MKC_B))
	{
		console_printf("position %.2f,%.2f,%.2f\n", GetTransform()->m_Position[0], GetTransform()->m_Position[1], GetTransform()->m_Position[2]);
	}



}

TstEntityCameraController::~TstEntityCameraController()
{
	if (engine->rendersys.m_camera == &m_Camera)
	{
		engine->rendersys.m_camera.reset();
	}
}
