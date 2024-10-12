#pragma once

#include "propdef.h"
#include "propdef_standard.h"
#include <mez/merize/data/color.h>

class PropDef_MezColor : PropDef
{
	typedef MezColor basetype;
public:
	static void create(propVec* f_v, basetype* f_val,const char* f_sector)
	{
		PropDef_Section::start(f_v, f_sector);
		PropDef_u8::create(f_v, &f_val->r, "r");
		PropDef_u8::create(f_v, &f_val->g, "g");
		PropDef_u8::create(f_v, &f_val->b, "b");
		PropDef_u8::create(f_v, &f_val->a, "a");
		PropDef_Section::end(f_v);
	}
};