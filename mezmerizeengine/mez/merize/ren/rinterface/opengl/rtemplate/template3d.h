#pragma once

#include "mez/merize/ren/rinterface/rtemplate/template.h"
#include "mez/merize/ren/rinterface/opengl/interface_opengl.h"
#include "mez/merize/ren/rinterface/opengl/gl_def.h"
#include <mez/merize/ren/rinterface/opengl/glmathstuff.h>

//handles pvms. :)

class RTemplate_3D : public RTemplate_2<RInterface_OpenGL>
{
public:
	unsigned int pvmloc = -1;
	virtual void ProgramUsed(RInterface_OpenGL* f_rinterface)
	{
		if (pvmloc == -1)
		{
			//todo: needs to be moved to the shader itself
			pvmloc = glGetUniformLocation(f_rinterface->m_ShaderProgram, "pvm");
		}

		assert(f_rinterface->m_transform);
		//todo: need to have pv cached before. or at least the projection
		matrix4_t matrix = GLMathStuff::GetPV(engine->rendersys.m_camera) * GLMathStuff::GetTransformationMatrix(f_rinterface->m_transform);


		glUniformMatrix4fv(pvmloc, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix[0]));
	}
};