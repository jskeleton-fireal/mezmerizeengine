#include "conhelper.h"
#include "cmd.h"

//This is the global s_helper.
static ConsoleHelper* s_helper = 0;
static bool s_initialized = 0;

ConsoleHelper::ConsoleHelper(bool f_global)
{
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
	if (!m_global)
	{
		//search global
		return FindGlobal()->FindConsoleThing(name);
	}
	return 0;
}

possibly_null(ConsoleVariable_Generic*) ConsoleHelper::FindConsoleVariable(const char* name)
{
	return dynamic_cast<ConsoleVariable_Generic*>(FindConsoleThing(name));
}

ConsoleHelper* ConsoleHelper::FindGlobal()
{
	if (!s_helper)
	{
		//create
		s_helper = new ConsoleHelper(true);
	}
	return s_helper;
}

ConsoleHelper* ConsoleHelper::FindCurrent()
{
	return &engine->conhelper;
}
