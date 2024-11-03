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

void TstEntityCameraController::Update()
{
	const float scale = (Input::KeyHeld(MKC_Q) ? 30 : 0.2f);
	GetTransform()->m_Position.z = 0;
	GetTransform()->m_Position.x = 0;
	//GetTransform()->m_Position.x = (cosf(engine->time * scale)) * 8;
	//GetTransform()->m_Position.y = sinf(engine->time * scale * 0.05f) * 8;
	Vector* pos = &m_Target.get()->m_ComponentContainer.FindTransform()->m_Transform.m_Position;
	if (m_Target)
	{
		GetTransform()->LookAt(*pos);
	}
	m_Camera.m_transform = *GetTransform();

	
	if (Input::KeyPressed(MKC_N))
	{
		console_printf("angle %.2f,%.2f,%.2f\n", GetTransform()->m_Angles.m_angles[0], GetTransform()->m_Angles.m_angles[1], GetTransform()->m_Angles.m_angles[2]);
	}
}

TstEntityCameraController::~TstEntityCameraController()
{
	if (engine->rendersys.m_camera == &m_Camera)
	{
		engine->rendersys.m_camera.reset();
	}
}
