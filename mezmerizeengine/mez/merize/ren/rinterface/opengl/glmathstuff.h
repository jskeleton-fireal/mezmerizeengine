#pragma once

//note: this includes glm. include this IF YOU PLAN on usnig gl math stuff


#include "../../camera.h"
#include "../../../deps/glm/glm.hpp"
#include "../../../deps/glm/matrix.hpp"
#include "../../../deps/glm/gtc/matrix_transform.hpp"

typedef glm::mat4 matrix4_t;

//glmathstuff lore: PVM => projection * view * model

static struct GLMathStuff
{
	//fov is assumed to be in radians
	static matrix4_t GetProjection_Perspective_Radians(float f_fov, float f_aspect, float f_nearplane, float f_farplane);
	static matrix4_t GetProjection_Perspective_Degrees(float f_fov, float f_aspect, float f_nearplane, float f_farplane);
	static matrix4_t GetProjection(MezCamera* f_camera);

	static matrix4_t TransformMatrix(matrix4_t f_mat,Vector f_pos);
	static matrix4_t RotateMatrix(matrix4_t f_mat,MezAngles f_pos);
	//this is the M in PVM
	//processes transformation before rotation. You want this for most models
	static matrix4_t GetTransformationMatrix(Transform* f_transform);
	//processes rotation before transformation. You want this for the camera
	static matrix4_t GetTransformationMatrix_Inverted(Transform* f_transform);

	//this is the PV in PVM
	static matrix4_t GetPV(MezCamera* f_camera);

};

//Think about it!