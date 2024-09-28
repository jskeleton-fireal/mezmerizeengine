#include "../mez/merize/console/cmd.h"
#include "gl_def.h"

extern "C"
{
	void glcc_Lol();
	const char* glerrortostring(int error_code);
}


void gl_verify_internal_immediate_operation()
{
	GLenum result = glGetError();
	const char* txt = glerrortostring(result);
	console_printf("%i - %s\n", result, txt);
	return;
}

CREATE_CONSOLECOMMAND_WFUNC(gl_verify, 0)
{
	engine->push_immediate_operation(gl_verify_internal_immediate_operation);
	return 0;
};

CREATE_CONSOLEVARIABLE_BOOL(gl_break, 0, false);

void glcc_Lol()
{
	if (ConsoleHelper::FindCurrent()->FindConsoleVariable("gl_break"))
	{
		DebugBreak();
	}
}

