#pragma once
#include <mez/merize/miscobjects/serializable/property_raw.h>
#include "../property_section.h"
class PropDef
{
public:
	typedef PropertiesVector propVec;
};


class PropDef_Section : public PropDef
{
public:
	static void start(propVec* f_v,const char* f_name)
	{
		f_v->push_back(new RawPropSection(f_name));
	}
	static void end(propVec* f_v)
	{
		f_v->push_back(new RawPropSection());
	}
};