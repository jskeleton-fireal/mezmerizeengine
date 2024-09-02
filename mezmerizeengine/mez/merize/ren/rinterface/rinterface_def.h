#pragma once
#include "rinterface.h"
#include "rstatic.h"

#if RENDERABLE_MODE == RENDER_MODE_OPENGL
class RInterface_OpenGL;
class RStatic_OpenGL;
#define RInterface_Default RInterface_OpenGL
#define RStatic_Default RStatic_OpenGL
#if  !defined(INTERFACE_OPENGL)
#include "opengl/interface_opengl.h"
#include "opengl/rstatic_opengl.h"
#endif
#else //no render system
class RInterface_Null;
#define RInterface_Default RInterface_Null

#endif