#pragma once
#include "mez/merize/engine/baseengine.h"
//This is what handles some more static stuff about rendering.
#define RINTERFACE_WINDOW_CLASS RENDER_WINDOW_CLASS*

//ex: some stuff that shouldnt be called for an instance

class RStatic
{
public:
	virtual void InitializeWindow(RINTERFACE_WINDOW_CLASS window) {}
	virtual void BeforeRender(RINTERFACE_WINDOW_CLASS window) {}
	virtual void AfterRender(RINTERFACE_WINDOW_CLASS window) {}

	virtual void Window_Resized(int new_width, int new_height) {}

};

typedef RStatic RStatic_Null;