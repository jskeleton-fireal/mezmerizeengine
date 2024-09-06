#ifndef RINTERFACE
#define RINTERFACE
#include "../../../version.h"
#include "../../merize.h"
#include "../../engine.h"
//rinterfaces are what connect renderables to the render system of choice

namespace sf
{
	class Window;
}
class RModel;
class RInterface
{
public:
	//member
	virtual void Initialize() = 0;
	virtual void UploadVerts(Vector verts[],int count = -1) = 0;
	virtual void UploadShader_Id(int shader_id) = 0;
	virtual void UploadShader(const char* shader_id) = 0;
	virtual void UploadShader_Vertex(const char* shader_id) = 0;
	virtual void LinkShaderProgram() = 0;
	virtual void Prepare() = 0; //set schtuff
	virtual void Draw() = 0;
	virtual void PostDraw() = 0; //reset stuff set by prepare
	//.. include a destructor as well
public:
	//defined by the interface
	bitfield64_t m_features = 0;
};


//this will never actually be used because if theres no render mode then render functions wont even be called.. but there still needs a class and function bodies since c++
//wont let you create instances of abstract classes which is fair
class RInterface_Null : public RInterface
{
	
};

#endif