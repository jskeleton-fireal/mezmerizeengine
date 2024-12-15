#include "cmd.h"
#include "../merize.h"
#include "../staticdefs.h"
#include "conhelper.h"

//this is for old code. do not use this
#define s_helper ConsoleHelper::FindCurrent()

ConsoleVariableBool cv_developer("developer", 0, false);


static void df_single(ConsoleHelper* c_curcon)
{
	
		int num = c_curcon->m_things.size();
		console_printf("ConsoleHelper = %x\n", c_curcon);
		console_printf("Count = %i\n", num);
		foreach_vector_fw(i, c_curcon->m_things)
		{
			auto* thing = c_curcon->m_things[i];
			console_printf("- %i <%s> t=(%s)\n", i, thing->m_Name, thing->ct_type_name());
		}
	
}

CREATE_CONSOLECOMMAND_WFUNC(dump_factories, CONTHING_FLAG_CONBALL)
{
	//dump factories :)
	df_single(ConsoleHelper::FindGlobal());

	return 0;
}

