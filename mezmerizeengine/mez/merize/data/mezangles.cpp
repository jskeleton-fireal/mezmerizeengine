#include <mez/merize/merize.h> //make sure this is included first
#include "mezangles.h"
#include "mezvector.h"
#include <mez/merize/console/console.h>

const float pi = 3.1415926535897932384626433832795f;
const float halfpi = pi / 2.0f;
const float qpi = pi / 4.0f;
const float dpi = pi * 2.0f;
float degtorad(float deg) { return deg * 0.0174533f; }
float radtodeg(float rad) { return rad * 57.2958f; }

MezAngles_Euler MezAngles::ToEuler()
{
    MezAngles_Euler e = MezAngles_Euler();
    e.m_angles[0] = GetEuler(0);
    e.m_angles[1] = GetEuler(1);
    e.m_angles[2] = GetEuler(2);
    return e;
}

float MezAngles::GetEuler(int index)
{
    return radtodeg(m_angles[index]);
}


void MezAngles::LookAt(Vector f_position_localspace)
{

    f_position_localspace.normalize_inplace();
    m_angles[ANGLE_PITCH] = -sinf(f_position_localspace.y);
    m_angles[ANGLE_YAW] = atan2f(-f_position_localspace.x, f_position_localspace.z);
    m_angles[ANGLE_ROLL] = 0.0f;
}

