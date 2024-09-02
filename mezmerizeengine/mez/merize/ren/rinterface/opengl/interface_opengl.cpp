#include "interface_opengl.h"
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GL/GL.h"
#include "GL/GLU.h"


void RInterface_OpenGL::Initialize()
{
	glGenBuffers(1, &(m_VertexBuffer));
	glGenVertexArrays(1, &m_VAO);
	m_ShaderProgram = glCreateProgram();

	assert(RIF_ISENABLED(m_VertexBuffer));
	assert(RIF_ISENABLED(m_VAO));
}

void RInterface_OpenGL::UploadVerts(Vector verts[], int count)
{
	m_vertcount = count;
	assert_msg(count > 0,"Cannot count verts in opengl"); //cannot count verts in opengl
	assert(RIF_ISENABLED(m_VertexBuffer));
	
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
	assert(RIF_ISENABLED(m_VertexBuffer));
	assert(RIF_ISENABLED(m_VAO));
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
