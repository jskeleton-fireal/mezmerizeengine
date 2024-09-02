#pragma once
#include "../../Engine.h"
//This is what handles some more static stuff about rendering.
#define RINTERFACE_WINDOW_CLASS RENDER_WINDOW_CLASS*

class RStatic
{
public:
	virtual void InitializeWindow(RINTERFACE_WINDOW_CLASS window) = 0;
	virtual void BeforeRender(RINTERFACE_WINDOW_CLASS window) = 0;
	virtual void AfterRender(RINTERFACE_WINDOW_CLASS window) = 0;

};