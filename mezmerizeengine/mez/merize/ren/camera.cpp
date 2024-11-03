#include "camera.h"

const auto radtodeg = 57.2957549575152f;

float MezCamera::getfov_deg()
{
    return m_fov * radtodeg;
}

void MezCamera::setfov_deg(float degrees)
{
    m_fov = degrees / radtodeg;
}
