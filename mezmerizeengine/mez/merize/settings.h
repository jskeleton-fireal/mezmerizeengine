#pragma once



enum
{
	RENDER_MODE_NORENDERING = 0,
	RENDER_MODE_OPENGL = 1,
};


#define RENDER_MODE RENDER_MODE_OPENGL


//support sfml's drawing tools. 0 by default
#define RENDER_SUPPORT_SFML_GRAPHICS 0

//alias
#define RENDERABLE_MODE RENDER_MODE

//ignore this. this will not be supported
#define SUPPORT_MULTIPLE_ENGINES 0
