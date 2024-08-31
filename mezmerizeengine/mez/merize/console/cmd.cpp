#include "cmd.h"
#include "../merize.h"
#include "../staticdefs.h"
#include "conhelper.h"

//this is for old code. do not use this
#define s_helper ConsoleHelper::FindCurrent()

CREATE_CONSOLEVARIABLE_BOOL(developer, 0, false);


static void df_single(ConsoleHelper* c_curcon)
{
	
		int num = c_curcon->m_things.size();
		console_printf("Current = %x (g=%i)\n", c_curcon,c_curcon->m_global);
		console_printf("Count = %i\n", num);
		foreach_vector_fw(i, c_curcon->m_things)
		{
			auto* thing = c_curcon->m_things[i];
			console_printf("- %i <%s> t=(%s)\n", i, thing->m_Name, thing->ct_type_name());
		}
	
}

CREATE_CONSOLECOMMAND_WFUNC(dump_factories, 0)
{
	//dump factories :)
	df_single(ConsoleHelper::FindGlobal());
	df_single(ConsoleHelper::FindCurrent());

	return 0;
}