#pragma once
#include "propdef.h"

class PropDef_float : PropDef
{
	typedef float basetype;
public:
	static void create(propVec* f_v, basetype* f_val, const char* f_name)
	{
		f_v->push_back(new RawProperty(f_val, sizeof(basetype), DataType::DT_Float, f_name));
	}
};

class PropDef_int : PropDef
{
	typedef int basetype;
public:
	static void create(propVec* f_v, basetype* f_val, const char* f_name)
	{
		f_v->push_back(new RawProperty(f_val, sizeof(basetype), DataType::DT_Int32, f_name));
	}
};
class PropDef_bool : PropDef
{
	typedef bool basetype;
public:
	static void create(propVec* f_v, basetype* f_val, const char* f_name)
	{
		f_v->push_back(new RawProperty(f_val, sizeof(basetype), DataType::DT_Boolean, f_name));
	}
};
class PropDef_u8 : PropDef
{
	typedef u8 basetype;
public:
	static void create(propVec* f_v, basetype* f_val, const char* f_name)
	{
		f_v->push_back(new RawProperty(f_val, sizeof(basetype), DataType::DT_Byte, f_name));
	}
};