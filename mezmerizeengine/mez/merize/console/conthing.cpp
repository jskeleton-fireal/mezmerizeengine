#include "conthing.h"
#include "../staticdefs.h"



enum {
	ENGINE_GLOBALREF_VAL = -1
};

ConsoleThing::ConsoleThing(const char* f_name, bitfield16_t f_flags)
{
	m_Name = f_name;
	m_Flags = f_flags;
	m_engine = get_engine_id();
	Upload();
}

//the idea for multi engine stuff is that theres a big factory of consolethings that gets created
//and for each engine it has its own consolehelper that copies everything from the big factory
bool ConsoleThing::is_global_reference()
{
	return m_engine== ENGINE_GLOBALREF_VAL;
}

void ConsoleThing::Upload()
{
	if (!ConsoleHelper::is_initialized())
	{
		//this will cause conhelper to intialize globally instead of in the engine
		ConsoleHelper::force_init();
	}
	ConsoleHelper::FindGlobal()->m_things.push_back(this);
}

int ConsoleThing::get_engine_id()
{
#if SUPPORT_MULTIPLE_ENGINES
	return engine->m_id;
#endif
	return 0;
}
