#include "EntityEnvironment.h"
#include <mez/merize/engine/BaseEngine.h>
ENTITY_LINK_EBALL(PROJECT_MEZMERIZE,"world_env", MezEntityEnvironment);

inline MezEntityEnvironment::MezEntityEnvironment()
{
	//set the environment in rendersys to this one
	engine->rendersys.enviro_sky.change(&m_environment.m_sky, false);
}

inline MezEntityEnvironment::~MezEntityEnvironment()
{
	if (engine->rendersys.enviro_sky == &m_environment.m_sky)
	{
		engine->rendersys.enviro_sky.change(0, 0);
	}
}
