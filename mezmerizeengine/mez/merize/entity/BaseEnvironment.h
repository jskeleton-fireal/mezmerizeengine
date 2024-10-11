#pragma once


#include "BaseEntity.h"
#include "mez/merize/data/entity_macros.h"
#include "mez/merize/data/environment.h"


//This is a base entity in case for any reason you need to derive from this.

class MezBaseEntityEnvironment : public MezBaseEntity
{
public:
	virtual environment_t GetEnvironment() = 0;
	virtual environment_sky_t GetSky() = 0;
	virtual environment_planet_t GetPlanet() = 0;
};