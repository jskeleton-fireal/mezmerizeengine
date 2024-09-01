#pragma once
#include "rinterface.h"

#if RENDERABLE_MODE == RENDER_MODE_OPENGL
class RInterface_OpenGL;
#define RInterface_Default RInterface_OpenGL
#if  !defined(INTERFACE_OPENGL)
#include "opengl/interface_opengl.h"
#endif
#else //no render system
class RInterface_Null;
#define RInterface_Default RInterface_Null

#endif