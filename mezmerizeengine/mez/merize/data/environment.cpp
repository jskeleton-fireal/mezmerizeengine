#include "environment.h"

//This exists so you dont need to recompile everything when you want to try new colors

void environment_sky_t::load_default_colors()
{
	 m_ambient = MezColor(0x7B7DB2);
	 m_diffuse = MezColor(0xFFCDBA);
	 m_specular = MezColor(0xFFFFFF);
}
