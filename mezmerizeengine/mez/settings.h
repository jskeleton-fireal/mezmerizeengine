#pragma once

//note: You! define your own PROJECT_<NAME>
//format is just a u64 id. do something unique

//in your engine you can set which project sets you want to be active at a time

//built in stuff, disable if you really really want to
#define PROJECT_MEZMERIZE 0x1
//testing engine stuff. mostly debugging stuff
#define PROJECT_TESTING 0x2


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
