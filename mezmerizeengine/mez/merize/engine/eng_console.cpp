#include "eng_console.h"
#include <string>
#include <iostream>

#include "mez/merize/console/conthing.h"
#include "mez/merize/console/cmd.h"
#include "mez/merize/console/cvhandler.h"
#include "mez/merize/console/conhelper.h"

#define s_helper ConsoleHelper::FindCurrent()

static bool validate_session()
{
	if (s_helper) return true;

	console_printf(" - Cannot execute: No engine\n");
	return 0;
}

void EngineConsole::process(BaseEngine* f_engine)
{
	std::string str;
	std::getline(std::cin, str);
	if (!validate_session()) return;
	process_single(f_engine, str.c_str());
	//console_printf("(last command : %s)\n", str.c_str());
	
}

void EngineConsole::process_single(BaseEngine* f_engine,const char* input)
{
	if (!input) return;
	if (!input[0]) return;
	//This kind of sucks but this is the safest way to do this
	ConCommandArgs args = ConCommandArgs(input);
	char tingname[80];
	args.Get(0).GetString(tingname, 80);

	//need to respect args n whatnot

	ConsoleThing* ting = s_helper->FindConsoleThing(tingname);
	if (!ting)
	{
		console_printf(" - Unknown operation: %s\n", tingname);
		return;
	}

	if (ting->is_oneshot())
	{
		console_printf(" - Executing operation: %s\n", tingname);
		int res = (int)ting->Execute(input);
		//..
		if (res)
			console_printf(" - Operation failed with error code %x\n", res);

		return;
	}
}
