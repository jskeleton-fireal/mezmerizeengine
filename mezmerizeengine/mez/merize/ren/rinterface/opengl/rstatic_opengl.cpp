#include "rstatic_opengl.h"
#include "gl_def.h"
#include "../rinterface.h"

const float half = 0.501960784f;

void RStatic_OpenGL::InitializeWindow(RINTERFACE_WINDOW_CLASS window)
{
	auto truwindow = window;
	truwindow->setActive(true);
	GLenum glewError = glewInit();
	assert(!glewError);
	glEnable(GL_DEPTH); //enable depth buffer
	glDepthFunc(GL_LESS); //Dont change this
	glPointSize(8);
	glLineWidth(3);

	//do a bunch of stuff i copy pasted this from phototropic idk what thsi doe
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, half, half, 1.0f);

	glViewport(0, 0, 400, 600);

	BeforeRender(window);
	AfterRender(window);
}

void RStatic_OpenGL::BeforeRender(RINTERFACE_WINDOW_CLASS window)
{
	auto truwindow = window;
	//make sure the window context is active
	truwindow->setActive(true);

	if (engine->rendersys[0]->available())
	{
		glClearColor(0.f, half, half, 0.0f);
	}
	else
	{
		glClearColor(half, 0.0f, 0.f, 0.0f);

	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RStatic_OpenGL::AfterRender(RINTERFACE_WINDOW_CLASS window)
{
	//swap buffers?
	auto truwindow = window;
	truwindow->display();
	//need to respect sfml's drawing tools if we are using the sfml window class thing
}

RStatic_OpenGL* RStatic_OpenGL::Get()
{
	return dynamic_cast<RStatic_OpenGL*>(engine->rendersys.m_rstatic);
}
