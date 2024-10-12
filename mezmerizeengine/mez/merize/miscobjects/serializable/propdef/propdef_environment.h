#pragma once
#include <mez/merize/data/environment.h>
#include "propdef.h"
#include "propdef_def.h"
#include "propdef_color.h"

class PropDef_environment_t : PropDef
{
	typedef environment_t basetype;
public:
	static void create(propVec* f_v, basetype* f_val)
	{
		PropDef_Section::start(f_v, "environment");
		PropDef_Vector::create(f_v, &f_val->m_sky.m_sun);
		PropDef_MezColor::create(f_v, &f_val->m_sky.m_diffuse, "diffuse");
		PropDef_MezColor::create(f_v, &f_val->m_sky.m_ambient, "ambient");
		PropDef_MezColor::create(f_v, &f_val->m_sky.m_specular, "specular");
		PropDef_float::create(f_v, &f_val->m_planet.m_gravity, "gravity");
		PropDef_Section::end(f_v);
	}
};