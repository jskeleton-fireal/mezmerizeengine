#pragma once
#include "../rstatic.h"
#include "glshader_cache.h"

class RStatic_OpenGL : public RStatic
{ public:
	virtual void InitializeWindow(RINTERFACE_WINDOW_CLASS window);
	virtual void BeforeRender(RINTERFACE_WINDOW_CLASS window);
	virtual void AfterRender(RINTERFACE_WINDOW_CLASS window);

	virtual void Window_Resized(int new_width, int new_height);
public:
	GLShaderCache m_cache_shader = GLShaderCache();
public:
	static RStatic_OpenGL* Get();
};