#include "mezangles.h"

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
