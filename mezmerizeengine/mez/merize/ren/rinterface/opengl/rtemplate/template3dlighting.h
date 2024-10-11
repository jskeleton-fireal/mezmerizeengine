#pragma once
#include "mez/merize/data/environment.h"
#include "template3d.h"

//handles pvms. :)

class RTemplate_3DLighting : public RTemplate_3D
{
public:
	bool initialized = false;
	unsigned int uniforms[5];
	virtual void ProgramUsed(RInterface_OpenGL* f_rinterface)
	{
		RTemplate_3D::ProgramUsed(f_rinterface);

		//For world lights, you need the light to be in local space to the model, so modelpos - lightpos

		if (!initialized)
		{
			initialized = 1;
			uniforms[0] = glGetUniformLocation(f_rinterface->m_ShaderProgram, "l_ambient");
			uniforms[1] = glGetUniformLocation(f_rinterface->m_ShaderProgram, "l_specular");
			uniforms[2] = glGetUniformLocation(f_rinterface->m_ShaderProgram, "l_sunlight");
			uniforms[3] = glGetUniformLocation(f_rinterface->m_ShaderProgram, "l_sun");
			uniforms[4] = glGetUniformLocation(f_rinterface->m_ShaderProgram, "l_rotation");
		}
		//rotation matrix of the model
		matrix4_t rotation_matrix = matrix4_t(1.0f);
		rotation_matrix = GLMathStuff::RotateMatrix(rotation_matrix, f_rinterface->m_transform->m_Angles);

		environment_sky_t* sky = engine->rendersys.enviro_sky;

		//this is terrible
		MezColorF colors[3]{ sky->m_ambient.Float(),sky->m_specular.Float() ,sky->m_light_sun.Float() };
		Vector sun = sky->m_sun;
		//sun.y = -sun.y; //in opengl -y = up

		glUniform3fv(uniforms[0], 1, reinterpret_cast<const GLfloat*>(&colors[0]));
		glUniform3fv(uniforms[1], 1, reinterpret_cast<const GLfloat*>(&colors[1]));
		glUniform3fv(uniforms[2], 1, reinterpret_cast<const GLfloat*>(&colors[2]));
		glUniform3fv(uniforms[3], 1, reinterpret_cast<const GLfloat*>(&sun));
		glUniformMatrix4fv(uniforms[4], 1, GL_FALSE,reinterpret_cast<const GLfloat*>(&rotation_matrix[0]));

	}
};