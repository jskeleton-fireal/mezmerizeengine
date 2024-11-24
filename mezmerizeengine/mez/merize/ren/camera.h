#pragma once
#include "mez/merize/data/transform.h"


class MezCamera
{
public:
	Transform m_transform;
	//This is in radians to speed up matrix calculations.
	float m_fov = 1.221731f; //approx 70 fov
	float m_nearplane = 0.01f;
	float m_farplane = 10000.0f;
	//set this if you want to override the aspect ratio
	float m_aspect_override = -0.0f;

	float getfov_deg();
	void setfov_deg(float degrees);

	float get_aspect();
};