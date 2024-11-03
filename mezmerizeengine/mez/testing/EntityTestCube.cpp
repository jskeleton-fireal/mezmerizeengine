#include "EntityTestCube.h"
#include "mez/merize/console/cmd.h"
#include "mez/merize/ren/model_selfdef.h"
#include "mez/merize/io/input.h"
#include <mez/merize/ren/rinterface/opengl/rstatic_opengl.h>

ENTITY_LINK(PROJECT_TESTING, "testcube", TstEntityTestCube_1);
ENTITY_LINK(PROJECT_TESTING, "testcube2", TstEntityTestCube_2);

inline void TstEntityTestCube_1::Initialize()
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
	PrecacheModel("freakbot.obj");
	PrecacheModel("testmodel.obj");
	PrecacheModel("ball.obj");
	SetModel("testmodel.obj");
	SetShader("modifiedphong", "default3d");
	SetLighting(true);
#endif

}

ConsoleVariableFloat cv_tc_scale = ConsoleVariableFloat("tc_scale", 0, 10.0f);
ConsoleVariableFloat cv_tc_x = ConsoleVariableFloat("tc_x", 0, 10.0f);
ConsoleVariableFloat cv_tc_z = ConsoleVariableFloat("tc_z", 0, 10.0f);
ConsoleVariableBool cv_tc_freeze = ConsoleVariableBool("tc_freeze", 0, false);
ConsoleVariableBool cv_tc_freeze2 = ConsoleVariableBool("tc_t", 0, 0);

void TstEntityTestCube_1::Update()
{
	if (Input::KeyPressed(MKC_B))
	{
		console_printf("cube %.2f,%.2f,%.2f\n", GetTransform()->m_Position.x, GetTransform()->m_Position.y, GetTransform()->m_Position.z);
	}	
	if (Input::KeyPressed(MKC_C))
	{
		console_printf("freeze\n");
		static bool x = 0;
		x = !x;
		cv_tc_freeze2.GetHandler()->Set_Internal(&x);
	}
	if (cv_tc_freeze2.GetBool())
	{
		GetTransform()->m_Position.x = cv_tc_x.GetFloat();
		GetTransform()->m_Position.z = cv_tc_z.GetFloat();
		return;
	}
	if (cv_tc_freeze.GetBool()) return;
	GetTransform()->m_Position.x = cosf(engine->time) * cv_tc_scale.GetFloat();
	GetTransform()->m_Position.z = sinf(engine->time) * cv_tc_scale.GetFloat();
}

#include <fstream>
void TstEntityTestCube_2::Initialize()
{
	TstEntityTestCube_1::Initialize();
	console_printf("> mezmerize testing : <testcube>\n");
	console_printf("wasd - move\n");
	console_printf("b - print pos\n");
	console_printf("v - reset pos\n");
	console_printf("n - print fps\n");
	console_printf("L - toggle lighting\n");
	console_printf("P - toggle lighting model\n");
	console_printf(". - wipe all cached items\n");
	console_printf("M - test serialization\n");
	console_printf(", - test deserialization\n");
	console_printf("1 - toggle model\n");
	console_printf("0 - delete self\n");
}
void TstEntityTestCube_2::Update()
{
#if 1
	const float scale = engine->time_delta * 0.2f;
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

	if (Input::KeyPressed(MKC_L))
	{
		static bool lit = 0;
		lit = !lit;
		SetLighting(lit);
		const char* travis = lit ? " " : " NOT ";
		console_printf("its%slit!!\n",travis);
	}

	if (Input::KeyPressed(MKC_P))
	{
		static bool shader = 0;
		shader = !shader;
		const char* which = shader ? "phong" : "modifiedphong";
		SetShader(which,"default3d");
		console_printf("using %s\n", which);
	}

	if (Input::KeyPressed(MKC_Period))
	{
		RStatic_OpenGL::Get()->m_cache_shader.wipe();
		console_printf("wipe\n");
	}	
	if (Input::KeyPressed(MKC_M))
	{
		const char* fn = "test.mzsr.txt";
		SerializeToFile(fn);
		console_printf("wrote to %s\n", fn);
	}	
	if (Input::KeyPressed(MKC_Comma))
	{
		const char* fn = "test.mzsr.txt";
		console_printf("reading from to %s\n", fn);

		char buffer[4000];

		std::fstream i;
		i.open(fn,std::ios::in);
		i.seekg(0, std::ios::beg);
		i.read(buffer, 4000);
		i.close();
		bool w = DeSerialize(buffer);
		console_printf("(should be 1) =====> %i\n",w);
	}	
	if (Input::KeyPressed(MKC_Num1))
	{
		console_printf("switched model\n");
		static bool c = 0;
		c = !c;
		SetModel(!c ? "freakbot.obj" : "ball.obj");
		SetShader("modifiedphong", "default3d");
		SetLighting(true);
	}	
	if (Input::KeyPressed(MKC_Num0))
	{
		console_printf("destroyed\n");
		Destroy();
	}	
	if (Input::KeyHeld(MKC_Num5))
	{		
		GetTransform()->m_Angles.LookAt(GetTransform()->m_Position);
	}
#endif
}

