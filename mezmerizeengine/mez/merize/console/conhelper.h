#pragma once
#include "../merize.h"

//dont include too much. this is included in engine.h

class ConsoleVariable_Generic;
class ConsoleThing;


class ConsoleHelper
{
public:
	stdvector<ConsoleThing*> m_things;
	bool m_global = 0;
public:
	ConsoleHelper(bool f_global = 0);
public:
	possibly_null(ConsoleThing*) FindConsoleThing(const char* name);
	possibly_null(ConsoleVariable_Generic*) FindConsoleVariable(const char* name);

	static ConsoleHelper* FindGlobal();
	static ConsoleHelper* FindCurrent();
	static bool is_initialized();
	static void force_init();

};