#include "glmathstuff.h"

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
    return GetProjection_Perspective_Radians(f_camera->m_fov, 4.0f / 3.0f, f_camera->m_nearplane, f_camera->m_farplane);
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
    matrix4_t matrix = RotateMatrix(matrix4_t(),f_transform->m_Angles);
    return TransformMatrix(matrix,f_transform->m_Position);
}

matrix4_t GLMathStuff::GetPV(MezCamera* f_camera)
{
    matrix4_t camera_projection = GetProjection(f_camera);
    matrix4_t camera_view = GetTransformationMatrix(&f_camera->m_transform);
    return camera_projection * camera_view;
}
