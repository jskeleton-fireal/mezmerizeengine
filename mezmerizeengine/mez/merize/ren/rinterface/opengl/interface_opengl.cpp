#include "interface_opengl.h"
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GL/GL.h"
#include "GL/GLU.h"

void RInterface_OpenGL::Static_InitializeWindow(trustmeptr(RINTERFACE_WINDOW_CLASS) window)
{
	itrustyou(window, RINTERFACE_WINDOW_CLASS);
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

	glClearColor(0, 0.501960784f, 0.501960784f, 1.0f);

	glViewport(0, 0, 400, 600);

	Static_BeforeRender(window);
	Static_AfterRender(window);
}

void RInterface_OpenGL::Static_BeforeRender(trustmeptr(RINTERFACE_WINDOW_CLASS) window)
{
	itrustyou(window, RINTERFACE_WINDOW_CLASS);
	//make sure the window context is active
	truwindow->setActive(true);

	if (engine->rendersys[0]->available())
	{
		glClearColor(0.f, 0.5f, 0.5f, 0.0f);
	}
	else
	{
		glClearColor(0.5f, 0.0f, 0.f, 0.0f);

	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RInterface_OpenGL::Static_AfterRender(trustmeptr(RINTERFACE_WINDOW_CLASS) window)
{
	//swap buffers?
	itrustyou(window, RINTERFACE_WINDOW_CLASS);
	truwindow->display();
	//need to respect sfml's drawing tools if we are using the sfml window class thing
}

void RInterface_OpenGL::Initialize()
{
	m_ShaderProgram = glCreateProgram();
	glGenBuffers(1, &(m_VertexBuffer));
	glGenVertexArrays(1, &m_VAO);
}

void RInterface_OpenGL::UploadVerts(Vector verts[], int count)
{
	m_vertcount = count;
	assert_msg(count > 0,"Cannot count verts in opengl"); //cannot count verts in opengl
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3i64  * count * sizeof(float), verts, GL_STATIC_DRAW);

	//Position Attribute
	glEnableVertexAttribArray(RIF_VAO_GL_POSITION);
	glVertexAttribPointer(
		0,
		3,                  // size
		GL_FLOAT,
		GL_FALSE,
		0,                  // stride
		(void*)0
	);
}

void RInterface_OpenGL::UploadShader(int shader_id)
{
	function_body_not_implemented;
}

void RInterface_OpenGL::UploadShader(const char* vertexshader, const char* fragmentshader)
{
}

void RInterface_OpenGL::Prepare()
{
	//respect m_features
	bool depth = 1;//!(m_features & RIF_FEATURE_GL_NO_DEPTH);
	if (depth) glEnable(GL_DEPTH); else glDisable(GL_DEPTH);
	bool cullface = 1;//!(m_features & RIF_FEATURE_GL_TWO_SIDED);
	if (cullface) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	//Need to transform matricies

	glEnableVertexAttribArray(RIF_VAO_GL_POSITION);

	//bind everything... yadda yadda


	glUseProgram(m_ShaderProgram);


	
}

void RInterface_OpenGL::Draw()
{
	//Draw
	glDrawArrays(GL_TRIANGLES, 0, m_vertcount);
}

void RInterface_OpenGL::PostDraw()
{
	glDisableVertexAttribArray(RIF_VAO_GL_POSITION);
}
