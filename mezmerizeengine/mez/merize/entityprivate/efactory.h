#pragma once
#include "../merize.h"
class MezBaseEntity;
typedef MezBaseEntity*(mezcreatefunc_t)();
//this is supposed to be hidden btw
class efactory_t
{ public:
	const char* m_name;
	mezcreatefunc_t* m_func;
	u64 m_project;

	efactory_t(const char* f_name, const mezcreatefunc_t* f_func);
	efactory_t(const char* f_name, const mezcreatefunc_t* f_func, u64 f_project);
};

class entity_factories_t
{
public:
	static efactory_t* find(const char* f_name,class BaseEngine* f_caller);
};

//vEProject: the PROJECT_<NAME> macro in settings.h  If the project flag is 0, entity will not be baked
//vEName: the classname you want for entity: (ex: "world_env")
//vEClassType: the actual class of the entity (ex: MezEntityEnvironment)
#define ENTITY_LINK(vEProject,vEName,vEClassType) const char* vEClassType::GetClassname() {return vEName;} void* ___fcrf##vEClassType##() {return new vEClassType();} efactory_t ____fc##vEClassType## = efactory_t(vEName,reinterpret_cast<mezcreatefunc_t*>(&___fcrf##vEClassType##),vEProject);