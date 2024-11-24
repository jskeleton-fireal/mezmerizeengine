#include "glmathstuff.h"
#include "../../../console/cmd.h"
void debug_log_matrix(matrix4_t it)
{
    console_printf("Matrix 4x4\n");
    for (int i = 0; i < 4; i++)
    {
        console_printf("> [%.2f,%.2f,%.2f,%.2f]\n", it[i][0], it[i][1], it[i][2], it[i][3]);
    }

}

matrix4_t GLMathStuff::GetProjection_Perspective_Degrees(float f_fov, float f_aspect, float f_nearplane, float f_farplane)
{
    return glm::perspective(f_fov * 0.0174533f, f_aspect, f_nearplane, f_farplane);
}

matrix4_t GLMathStuff::GetProjection_Perspective_Radians(float f_fov, float f_aspect, float f_nearplane, float f_farplane)
{
    return glm::perspective(f_fov, f_aspect, f_nearplane, f_farplane);
}

matrix4_t GLMathStuff::GetProjection(MezCamera* f_camera)
{
    return GetProjection_Perspective_Radians(f_camera->m_fov, f_camera->get_aspect(), f_camera->m_nearplane, f_camera->m_farplane);
}

matrix4_t GLMathStuff::TransformMatrix(matrix4_t f_mat, Vector f_pos)
{
    return glm::translate(f_mat, *reinterpret_cast<glm::vec3*>(&f_pos));
}

matrix4_t GLMathStuff::RotateMatrix(matrix4_t f_mat, MezAngles f_pos)
{
    f_mat = glm::rotate(f_mat, f_pos.m_angles[0], glm::vec3(1, 0, 0));
    f_mat = glm::rotate(f_mat, f_pos.m_angles[1], glm::vec3(0, 1, 0));
    f_mat = glm::rotate(f_mat, f_pos.m_angles[2], glm::vec3(0, 0, 1));
    return f_mat;
}

matrix4_t GLMathStuff::GetTransformationMatrix(Transform* f_transform)
{
    matrix4_t matrix = matrix4_t(1.0f);

    matrix = TransformMatrix(matrix, f_transform->m_Position);
    return RotateMatrix(matrix, f_transform->m_Angles);   

}

matrix4_t GLMathStuff::GetTransformationMatrix_Inverted(Transform* f_transform)
{
    matrix4_t matrix = matrix4_t(1.0f);

    matrix = RotateMatrix(matrix, f_transform->m_Angles);
    return TransformMatrix(matrix, -f_transform->m_Position);

}

matrix4_t GLMathStuff::GetPV(MezCamera* f_camera)
{
    matrix4_t camera_projection = GetProjection(f_camera);
    matrix4_t camera_view = GetTransformationMatrix_Inverted(&f_camera->m_transform);

    matrix4_t pv = camera_projection * camera_view;
    //debug_log_matrix(pv);
    return pv;
}
