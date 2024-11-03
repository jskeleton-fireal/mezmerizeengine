#include <mez/merize/merize.h> //make sure this is included first
#include "mezangles.h"
#include "mezvector.h"
#include <mez/merize/console/console.h>

const float pi = 3.1415926535897932384626433832795f;
const float hpi = pi / 2.0f; //1.5707963267948966192313216916398
const float qpi = pi / 4.0f; //0.78539816339744830961566084581988
const float dpi = pi * 2.0f; //6.283185307179586476925286766559

// 1 / sqrt(2)
const float norma = 0.70710678118654752440084436210485f;

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
    //TODO FIXME: this is off..
    m_angles[ANGLE_PITCH] = -tanf(f_position_localspace.y);
    m_angles[ANGLE_YAW] = atan2f(-f_position_localspace.x, f_position_localspace.z);
    //does this need to be set?
    m_angles[ANGLE_ROLL] = 0.0f;
}

Vector MezAngles::ForwardVector()
{
    Vector v = Vector();
    //get the pitch first
    v.y = -sin(m_angles[ANGLE_PITCH]);
    float scale = cos(m_angles[ANGLE_PITCH]);
    v.x = sin(m_angles[ANGLE_YAW]) * scale;
    v.z = -cos(m_angles[ANGLE_YAW]) * scale;
    return v;
}

Vector MezAngles::RightVector_2D()
{
    Vector v = Vector();
    v.y = 0;
    v.x = -cos(m_angles[ANGLE_YAW]);
    v.z = sin(m_angles[ANGLE_YAW]);
    return v.normalize();
}

Vector MezAngles::RightVector_3D()
{
    Vector v = Vector();
    v.y = -sin(m_angles[ANGLE_YAW]);
    float scale = cos(m_angles[ANGLE_ROLL]);
    v.x = -cos(m_angles[ANGLE_YAW]) * scale;
    v.z = sin(m_angles[ANGLE_YAW]) * scale;
    return v.normalize();
}

Vector MezAngles::UpVector()
{
    abort(); //not implemented yet LOL im going to sleep after i push this
}

