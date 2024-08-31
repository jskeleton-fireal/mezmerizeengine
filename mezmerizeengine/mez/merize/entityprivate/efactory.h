#pragma once
#include "../merize.h"
class MezBaseEntity;
typedef MezBaseEntity*(mezcreatefunc_t)();
//this is supposed to be hidden btw
class efactory_t
{ public:
	const char* m_name;
	mezcreatefunc_t* m_func;

	efactory_t(const char* f_name, const mezcreatefunc_t* f_func);
};

class entity_factories_t
{
public:
	static efactory_t* find(const char* f_name);
};

#define ENTITY_LINK(vEName,vEClassType) static void* ___fcrf() {return new vEClassType();} static efactory_t ____fc = efactory_t(vEName,reinterpret_cast<mezcreatefunc_t*>(&___fcrf));