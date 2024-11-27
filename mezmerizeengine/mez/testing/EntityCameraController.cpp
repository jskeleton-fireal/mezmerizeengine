#include "EntityCameraController.h"
#include <mez/merize/merize.h>
#include <mez/merize/engine/BaseEngine.h>
#include <mez/merize/io/input.h>
#include <mez/merize/console/cmd.h>
ENTITY_LINK(PROJECT_TESTING, "controller_camera", TstEntityCameraController);
ConsoleVariableFloat cv_dis("dis", 0, 10.0f);
ConsoleVariableBool cv_x("x", 0, 0);

void TstEntityCameraController::Initialize()
{
	MezEntity3DTransform::Initialize();
	engine->rendersys.m_camera.change(&m_Camera, false);
	//needs to be removed
	MezEntity3DTransform* target = MezBaseEntity::Find<MezEntity3DTransform>("testcube");
	if (target)
	{
		m_Target = target->GetEHandle();
	}
	Input::CursorLock(true);
}
void TstEntityCameraController::Update()
{
	//todo: add modes to the camera controller and split up the oldupdate func to be separate modes
	Freecam();

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

void TstEntityCameraController::Freecam()
{
	Vector2 mpos_delta = Input::GetMousePos_Normalized_Delta();

	const float camera_look_speed = 4.0f;
	const float camera_move_speed = 8.0f;

	Transform* transform = GetTransform();

	if (mpos_delta.x || mpos_delta.y)
	{
		

		transform->m_Angles.m_angles[ANGLE_PITCH] += mpos_delta.y * camera_look_speed;
		transform->m_Angles.m_angles[ANGLE_YAW] += mpos_delta.x * camera_look_speed;
		
	}

	float x = Input::KeyFWAxis(MKC_W, MKC_S) * camera_move_speed;
	float z = Input::KeyFWAxis(MKC_A, MKC_D) * camera_move_speed;
	transform->m_Position += transform->m_Angles.ForwardVector() * x * engine->time_delta;
	transform->m_Position += transform->m_Angles.RightVector_3D() * z * engine->time_delta;
}


void TstEntityCameraController::OldUpdate()
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


	




}

TstEntityCameraController::~TstEntityCameraController()
{
	if (engine->rendersys.m_camera == &m_Camera)
	{
		engine->rendersys.m_camera.reset();
	}
	Input::CursorLock(0);
}
