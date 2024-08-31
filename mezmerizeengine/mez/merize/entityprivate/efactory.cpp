#include "efactory.h"
#if SUPPORT_MULTIPLE_ENGINES
#error "efactory.cpp needs to be refactored to support multiple engines"
#endif

class efac_INTERNAL
{
public:
	stdvector< efactory_t*> factories;
	void upload(efactory_t* ref)
	{
		factories.push_back(ref);
	}
};
static efac_INTERNAL f;

efactory_t::efactory_t(const char* f_name, const mezcreatefunc_t* f_func)
{
	m_name = f_name;
	m_func = f_func;
	f.upload(this);
}

efactory_t* entity_factories_t::find(const char* f_name)
{
	assert(f.factories.size());
	for (int i = 0; i < f.factories.size(); i++)
	{
		if (!strcmp(f.factories[i]->m_name, f_name))
		{
			return f.factories[i];
		}
	}
	return nullptr;
}
