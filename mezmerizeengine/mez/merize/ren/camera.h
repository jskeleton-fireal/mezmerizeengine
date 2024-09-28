#pragma once
#include "../transform.h"


class MezCamera
{
public:
	Transform m_transform;
	//This is in radians to speed up matrix calculations.
	float m_fov = 1.221731f; //approx 70 fov
	float m_nearplane = 0.01f;
	float m_farplane = 500.0f;


};