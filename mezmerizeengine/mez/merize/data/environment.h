#pragma once

#include "mez/merize/data/color.h"
#include "mez/merize/data/mezangles.h"

//note: im probably gonna change all of this.

//sky part of the environment. used for passing lighting info to shaders
struct environment_sky_t
{
	//sky related stuff
	MezColor m_ambient = MezColor(0x17213D);
	MezColor m_light_sun = MezColor(0xFFF8C5);
	MezColor m_specular = MezColor(0xFFFFFF);
	Vector m_sun = Vector(0.5f, 0.8f, 0.0f);
};
//planet specific stuff. probably should rename this to world or something 
struct environment_planet_t
{
	float m_gravity = 9.8f;
};

//this is what is stored in MezEntityEnvironment
struct environment_t
{
	environment_planet_t m_planet = environment_planet_t();
	environment_sky_t m_sky = environment_sky_t();
};