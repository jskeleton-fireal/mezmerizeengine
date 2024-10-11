#pragma once
#include "BaseEnvironment.h"


//some environment information

class MezEntityEnvironment : public MezBaseEntityEnvironment
{
	DECLARE_ENTITY(MezEntityEnvironment);
public:
	environment_t m_environment;
	virtual environment_t GetEnvironment() { return m_environment; }
	virtual environment_sky_t GetSky() { return m_environment.m_sky; }
	virtual environment_planet_t GetPlanet() { return m_environment.m_planet; }
};