#include "conhelper.h"
#include "cmd.h"

//This is the global s_helper.
static ConsoleHelper* s_helper = 0;
static bool s_initialized = 0;

ConsoleHelper::ConsoleHelper(bool f_global)
{
	f_global = !s_helper;
	if (f_global)
	{
		assert(!s_helper);
		s_helper = this;
		s_initialized = 1;
		//need to also set s_helper to 0 if this gets deleted for some reason
	}
	m_global = f_global;
	console_printf("created new console helper (GLOBAL=%i\n", f_global);
}

possibly_null(ConsoleThing*) ConsoleHelper::FindConsoleThing(const char* name)
{
	foreach_vector_bw(i, m_things)
	{
		if (!strcmp(m_things[i]->m_Name, name))
		{
			return m_things[i];
		}
	}
	return 0;
}

possibly_null(ConsoleVariable_Generic*) ConsoleHelper::FindConsoleVariable(const char* name)
{
	return dynamic_cast<ConsoleVariable_Generic*>(FindConsoleThing(name));
}

ConsoleHelper* ConsoleHelper::FindGlobal()
{
	return s_helper;
}

ConsoleHelper* ConsoleHelper::FindCurrent()
{
	return engine->conhelper;
}

bool ConsoleHelper::is_initialized()
{
	return s_initialized;
}

void ConsoleHelper::force_init()
{
	if (is_initialized()) return;
	s_helper = new ConsoleHelper(true);
	s_initialized = 1;
}
