#pragma once


#include "propdef.h"
#include "propdef_standard.h"
#include <mez/merize/data/transform.h>

class PropDef_Vector : PropDef
{
	typedef Vector basetype;
public:
	static void create(propVec* f_v, basetype* f_val,const char* f_sector = "vec3")
	{
		PropDef_Section::start(f_v, f_sector);
		PropDef_float::create(f_v, &f_val->x, "x");
		PropDef_float::create(f_v, &f_val->y, "y");
		PropDef_float::create(f_v, &f_val->z, "z");
		PropDef_Section::end(f_v);
	}
};

class PropDef_MezAngles : PropDef
{
	typedef MezAngles basetype;
public:
	static void create(propVec* f_v, basetype* f_val, const char* f_sector = "ang")
	{
		PropDef_Section::start(f_v, f_sector);
		PropDef_float::create(f_v, &f_val->m_angles[0], "0");
		PropDef_float::create(f_v, &f_val->m_angles[1], "1");
		PropDef_float::create(f_v, &f_val->m_angles[2], "2");
		PropDef_Section::end(f_v);
	}
};


class PropDef_Transform : PropDef
{
	typedef Transform basetype;
public:
	static void create(propVec* f_v, basetype* f_val)
	{
		PropDef_Section::start(f_v,"transform");
		PropDef_Vector::create(f_v, &f_val->m_Position, "pos");
		PropDef_MezAngles::create(f_v, &f_val->m_Angles, "ang");
		PropDef_Section::end(f_v);
	}
};