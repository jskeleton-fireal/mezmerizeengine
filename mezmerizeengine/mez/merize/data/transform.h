#pragma once
#include "mez/merize/merize.h"
#include "mez/merize/data/mezangles.h"
class Transform
{
public:
	Vector m_Position;
	MezAngles m_Angles;

	void LookAt(Vector f_worldspace_position);
};

