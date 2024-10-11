
//to run an engine, do this.
//note: 
//	you probably want to disable any engines that you arent using, their entities/cmds will still be built regardless of if you actually use their engine.
#include "mez/testing/Engine_Testing.h"
int main()
{
	{
		BaseEngine* engine = new Engine_Testing();
		return engine->run();
	}
	return -1;
}