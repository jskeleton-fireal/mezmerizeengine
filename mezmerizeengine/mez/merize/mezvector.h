#pragma once


struct Vector
{
	//for easy
	float x;
	float y;
	float z;
#ifdef __cplusplus 
	//for backwards compatibility
	float operator [] (int i) { return (&reintrp(*this, float))[i]; }
#endif
};
