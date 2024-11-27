#include "efactory.h"
#if SUPPORT_MULTIPLE_ENGINES
#error "efactory.cpp needs to be refactored to support multiple engines"
#endif

#include <mez/merize/engine/BaseEngine.h>

//internal efac identifier
class efac_INTERNAL
{
public:
	struct efac_it2
	{
		stdvector< efactory_t*> factories;
	};
public:
	//Need to ensure this gets initialized before we start adding stuff to it
	efac_it2* fac=0;
	void upload(efactory_t* ref)
	{
		if (!fac)
		{
			fac = new efac_it2();
		}
		//creating a new one here to make sure it doesnt get freed (This happens sometimes and im not sure why)
		efactory_t* clone = new efactory_t(*ref);
		fac->factories.push_back(clone);
	}
};
static efac_INTERNAL f;

efactory_t::efactory_t(const char* f_name, const mezcreatefunc_t* f_func)
{
	m_name = f_name;
	m_func = f_func;
	f.upload(this);
}

efactory_t::efactory_t(const char* f_name, const mezcreatefunc_t* f_func, u64 f_project)
{
	m_project = f_project;
	m_name = f_name;
	m_func = f_func;
	f.upload(this);
	
}

efactory_t* entity_factories_t::find(const char* f_name, class BaseEngine* f_caller)
{
	assert(f.fac->factories.size());
	for (int i = 0; i < f.fac->factories.size(); i++)
	{
		efactory_t* x = f.fac->factories.at(i);

		bool match = !strcmp(x->m_name, f_name);
		if (!match) continue;
		bool project = f_caller->ProjectIdIsValid(x->m_project);
		if (!project) continue;


		return x;
	}
	return nullptr;
}