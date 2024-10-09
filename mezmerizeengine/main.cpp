#include "mez/merize/Engine_Testing.h"


int main()
{
	{
		BaseEngine* engine = new Engine_Testing();
		return engine->run();
	}
	return -1;
}