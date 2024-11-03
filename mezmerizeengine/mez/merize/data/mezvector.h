#pragma once
#ifndef MEZ_VECTOR_H
#define MEZ_VECTOR_H
struct Vector
{
	//for easy
	float x;
	float y;
	float z;
#ifdef __cplusplus 
	//for backwards compatibility
	float operator [] (int i) { return (&reintrp(*this, float))[i]; }
	Vector operator-(Vector i) { return Vector(x-i.x,y-i.y,z-i.z); }
	Vector operator+(Vector i) { return Vector(x+i.x,y+i.y,z+i.z); }
	Vector operator*(Vector i) { return Vector(x*i.x,y*i.y,z*i.z); }
	Vector operator/(Vector i) { return Vector(x/i.x,y/i.y,z/i.z); }
	Vector operator*(float i) { return Vector(x*i,y*i,z*i); }
	Vector operator/(float i) { return Vector(x/i,y/i,z/i); }
	Vector normalize();
	void normalize_inplace();
	float magnitude();
	//instead of 0.76,0.76 its 1,1. better for some maths. idk what this is called mathematically.
	//expects an already normalzied vector for perf
	void fakenormalize_inplace();
#endif
};
#endif