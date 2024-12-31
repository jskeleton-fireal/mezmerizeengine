#pragma once
#include "BaseEntity.h"
#include <mez/merize/data/environment.h>
#include "mez/merize/data/entity_macros.h"


//entity wrapper for environment

class MezEntityEnvironment : public MezBaseEntity
{
	DECLARE_ENTITY(MezEntityEnvironment);
public:
	environment_t m_environment;
	virtual environment_t GetEnvironment() { return m_environment; }
	virtual environment_sky_t GetSky() { return m_environment.m_sky; }
	virtual environment_planet_t GetPlanet() { return m_environment.m_planet; }

	MezEntityEnvironment();
	~MezEntityEnvironment();

};