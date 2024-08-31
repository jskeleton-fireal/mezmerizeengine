#pragma once

//this is very niche.. this was supposed to be supported from the start
//but factories and whatnot make this a lot more complicated to set up
//setting this to 0 basically stubs out everything that handles multiple
//engines, which is faster to run code in which is GOOD!
//potential use cases: client hosting servers, or something
//The best way for this to work is to just have multiple programs running or something however that works i dont really care right now
#define SUPPORT_MULTIPLE_ENGINES 0

enum
{
	RENDER_MODE_NORENDERING = 0,
	RENDER_MODE_OPENGL = 1,
};


#define RENDERABLE_MODE RENDER_MODE_OPENGL


//support sfml's drawing tools. 0 by default due to extra cpu usage
#define RENDER_SUPPORT_SFML_GRAPHICS 0