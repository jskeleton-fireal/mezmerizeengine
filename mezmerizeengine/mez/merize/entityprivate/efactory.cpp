#include "efactory.h"
#include <mez/merize/engine/BaseEngine.h>
#include "efactory_private.h"

efac_INTERNAL the_efac_internal;
#define f the_efac_internal

efactory_t::efactory_t(const char* f_name, const mezcreatefunc_t* f_func)
{
	m_name = f_name;
	m_func = f_func;
	m_flags = 0;
	m_project = 0;
	f.upload(this);
}

efactory_t::efactory_t(const char* f_name, const mezcreatefunc_t* f_func, u64 f_project, int f_flags)
{
	m_project = f_project;
	m_name = f_name;
	m_func = f_func;
	m_flags = f_flags;

	if (f_flags & EFACTORY_FLAGS_EBALL) { return; }
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