#pragma once

//i dont care if quaternions are better. 3 is less than 4 and thats less space to store
//IF YOU NEED QUATERNIONS imlpement a converter or something i DO NOT CARE ABOUT YOU.

enum
{
	ANGLE_PITCH, //like player looking up and down
	ANGLE_YAW, //like player looking left and right
	ANGLE_ROLL, //sidways movement
};
struct MezAngles;
struct Vector;
typedef MezAngles MezAngles_Euler;
struct MezAngles
{
	//stored as radians
	float m_angles[3];

	MezAngles_Euler ToEuler();
	float GetEuler(int index);

	MezAngles() { m_angles[0] = 0; m_angles[1] = 0; m_angles[2] = 0; }
	MezAngles(float p,float y,float r) { m_angles[0] = p; m_angles[1] = y; m_angles[2] = r; }
	MezAngles(float p,float y) { m_angles[0] = p; m_angles[1] = y; m_angles[2] = 0; }

	void LookAt(Vector f_position_localspace);
	Vector ForwardVector();
	//2d ignores roll
	Vector RightVector_2D();
	Vector RightVector_3D();
	Vector UpVector();
};