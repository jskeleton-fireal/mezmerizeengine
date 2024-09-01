#ifndef RINTERFACE
#define RINTERFACE
#include "../../../version.h"
#include "../../merize.h"
#include "../../engine.h"
//rinterfaces are what connect renderables to the render system of choice


#define RINTERFACE_WINDOW_CLASS RENDER_WINDOW_CLASS

//ignore this :)
#define RINTERFACE_LAMEHACK ;

//These are everything that needs to be defined in a rinterface
#define RINTERFACE_DEFINE_STATIC_FUNCS 	\
static void Static_InitializeWindow(trustmeptr(RINTERFACE_WINDOW_CLASS) window) RINTERFACE_LAMEHACK	\
static void Static_BeforeRender(trustmeptr(RINTERFACE_WINDOW_CLASS) window) RINTERFACE_LAMEHACK \
static void Static_AfterRender(trustmeptr(RINTERFACE_WINDOW_CLASS) window) RINTERFACE_LAMEHACK \

namespace sf
{
	class Window;
}
class RModel;
class RInterface
{
public:
	//Static functions you must define
	illusionary(RINTERFACE_DEFINE_STATIC_FUNCS);
public:
	//member
	virtual void Initialize() = 0;
	virtual void UploadVerts(Vector verts[],int count = -1) = 0;
	virtual void UploadShader(int shader_id) = 0;
	virtual void Prepare() = 0; //set schtuff
	virtual void Draw() = 0;
	virtual void PostDraw() = 0; //reset stuff set by prepare
	//.. include a destructor as well
public:
	//defined by the interface
	bitfield64_t m_features = 0;
};

#undef RINTERFACE_LAMEHACK
//#define RINTERFACE_LAMEHACK {}
#define RINTERFACE_LAMEHACK {function_body_not_implemented;}
//this will never actually be used because if theres no render mode then render functions wont even be called.. but there still needs a class and function bodies since c++
//wont let you create instances of abstract classes which is fair
class RInterface_Null : public RInterface
{
	RINTERFACE_DEFINE_STATIC_FUNCS
};

#undef RINTERFACE_LAMEHACK
#define RINTERFACE_LAMEHACK ;
#endif