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
#include "rtemplate/template_def.h"

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
	assert_msg(count > 0,"Cannot count verts in opengl"); //cannot count verts in opengl bc im lazy
	assert(RIF_ISENABLED(m_VertexBuffer));
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);



	glBindVertexArray(m_VAO);
	//Position Attribute
	glEnableVertexAttribArray(RIF_VAO_GL_POSITION);
	glVertexAttribPointer(
		RIF_VAO_GL_POSITION,
		3,                  // size
		GL_FLOAT,
		GL_FALSE,
		0,                  // stride
		(void*)0
	);

	//upload verts
	glBufferData(GL_ARRAY_BUFFER, 3i64 * count * sizeof(float), verts, GL_DYNAMIC_DRAW);
}

void RInterface_OpenGL::UploadNormals(Vector normals[], int count)
{
	m_vertcount = count;
	assert_msg(count > 0, "Cannot count normals in opengl"); //cannot count normals in opengl bc im lazy
	assert(RIF_ISENABLED(m_VertexBuffer));
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	if (m_VAO_normal ==-1)
	{
		glGenBuffers(1, &m_VAO_normal);
	}
	glBindBuffer(GL_ARRAY_BUFFER,m_VAO_normal);
	//normal Attribute
	glEnableVertexAttribArray(RIF_VAO_GL_NORMAL);
	glVertexAttribPointer(
		RIF_VAO_GL_NORMAL,
		3,                  // size
		GL_FLOAT,
		GL_TRUE, //GL_FALSE,
		0,                  // stride
		(void*)0
	);

	//upload normals
	glBufferData(GL_ARRAY_BUFFER, 3i64 * count * sizeof(float), normals, GL_DYNAMIC_DRAW);

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

		engine->show_messagebox(errormsg, ENGINE_MSGBOXTYPE_ERROR);
			

		// In this simple program, we'll just leave
		return;
	}
#endif
}

void RInterface_OpenGL::RegenerateProgram()
{
	glDeleteProgram(m_ShaderProgram);
	m_ShaderProgram = -1;
	m_ShaderProgram = glCreateProgram();
}


void RInterface_OpenGL::Prepare()
{
#if 1
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
#else
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
#endif
	assert(RIF_ISENABLED(m_VertexBuffer));
	assert(RIF_ISENABLED(m_VAO));
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	glEnableVertexAttribArray(RIF_VAO_GL_POSITION);
	glBindVertexArray(m_VAO);

	glEnableVertexAttribArray(RIF_VAO_GL_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER,m_VAO_normal);

	//Need to transform matricies


	//bind everything... yadda yadda

	glUseProgram(m_ShaderProgram);

	if (m_template)
	{
		m_template->ProgramUsed(this);
	}

	
	
}

void RInterface_OpenGL::Draw()
{
//#define GL_POINTS 0x0000
//#define GL_LINES 0x0001
//#define GL_LINE_LOOP 0x0002
//#define GL_LINE_STRIP 0x0003
//#define GL_LINE_BIT 0x00000004
//#define GL_TRIANGLES 0x0004
//#define GL_TRIANGLE_STRIP 0x0005
//#define GL_TRIANGLE_FAN 0x0006
//#define GL_QUADS 0x0007
//#define GL_QUAD_STRIP 0x0008
//#define GL_POLYGON_BIT 0x00000008
//#define GL_POLYGON 0x0009
	//Draw
	glDrawArrays(m_drawmode, 0, m_vertcount);
}

void RInterface_OpenGL::PostDraw()
{
	glDisableVertexAttribArray(RIF_VAO_GL_POSITION);
	glDisableVertexAttribArray(RIF_VAO_GL_NORMAL);
	
}



void RInterface_OpenGL::RequestFeature(rinterface_feature_t feature)
{
	switch (feature)
	{
	case RINTERFACE_FEATURE_NONE:
		if (m_template) delete m_template;
		m_template = 0;
		break;
	case RINTERFACE_FEATURE_3D:
		if (m_template) delete m_template;
		m_template = new RTemplate_3D();
		break;	
	case RINTERFACE_FEATURE_3DLIGHTING:
		if (m_template) delete m_template;

		m_template = new RTemplate_3DLighting();
		break;
	}
}
