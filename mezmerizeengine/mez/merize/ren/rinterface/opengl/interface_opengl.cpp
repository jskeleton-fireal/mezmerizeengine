#include "interface_opengl.h"
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GL/GL.h"
#include "GL/GLU.h"
#include "glshader.h"
#include "glshader_cache.h"
#include "rstatic_opengl.h"
#include "../../../console/cmd.h"
#include "glmathstuff.h"

#define AND_GL_DEBUGGING_STUFF 1


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
	glBindVertexArray(m_VAO);

	//upload verts
	glBufferData(GL_ARRAY_BUFFER, 3i64  * count * sizeof(float), &verts[0], GL_DYNAMIC_DRAW);

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

void RInterface_OpenGL::UploadShader_Id(int shader_numeric_id)
{
	function_body_not_implemented;
}

void RInterface_OpenGL::UploadShader(const char* shader_id)
{
	GLShader* shader = RStatic_OpenGL::Get()->m_cache_shader.Lookup_sId(shader_id,GLShaderCache::GLSHADERTYPE_FRAGMENT);
	assert(shader);
	AttachShader(shader);
}

void RInterface_OpenGL::UploadShader_Vertex(const char* shader_id)
{
	GLShader* shader = RStatic_OpenGL::Get()->m_cache_shader.Lookup_sId(shader_id, GLShaderCache::GLSHADERTYPE_VERTEX);
	assert(shader);
	AttachShader(shader);
}

void RInterface_OpenGL::AttachShader(GLShader* shader)
{
	glAttachShader(m_ShaderProgram, shader->m_shader);
}
void RInterface_OpenGL::LinkShaderProgram()
{
	glLinkProgram(m_ShaderProgram);

#if AND_GL_DEBUGGING_STUFF
	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength;
		glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		char errormsg[800];
		glGetProgramInfoLog(m_ShaderProgram, maxLength, &maxLength, errormsg);
		// Use the infoLog as you see fit.

		//hopefully this works
		console_printf("%s\n", errormsg);

		// In this simple program, we'll just leave
		return;
	}
#endif
}


void RInterface_OpenGL::Prepare()
{
#if 0
	//respect m_features
	bool depth = 1;//!(m_features & RIF_FEATURE_GL_NO_DEPTH);
	if (depth) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	bool cullface = 1;//!(m_features & RIF_FEATURE_GL_TWO_SIDED);
	if (cullface) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
#else
#if 0
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
#else
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
#endif
#endif
	assert(RIF_ISENABLED(m_VertexBuffer));
	assert(RIF_ISENABLED(m_VAO));
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBindVertexArray(m_VAO);
	//Need to transform matricies

	glEnableVertexAttribArray(RIF_VAO_GL_POSITION);

	//bind everything... yadda yadda

	glUseProgram(m_ShaderProgram);

	unsigned int pvmloc = glGetUniformLocation(m_ShaderProgram, "pvm");

	//This shader wants a pvm
	if (pvmloc >= 0)
	{
		//todo: need to have pv cached before
		matrix4_t matrix = GLMathStuff::GetPV(engine->rendersys.m_camera) * GLMathStuff::GetTransformationMatrix(m_transform);


		glUniformMatrix4fv(pvmloc, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix[0]));
	}

	
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
