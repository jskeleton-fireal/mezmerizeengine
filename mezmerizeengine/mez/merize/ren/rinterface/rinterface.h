#ifndef RINTERFACE
#define RINTERFACE
#include "mez/merize/version.h"
#include "mez/merize/merize.h"
#include "mez/merize/engine/baseengine.h"
//rinterfaces are what connect renderables to the render system of choice

namespace sf
{
	class Window;
}
class RModel;
class RInterface
{
public:
	Transform* m_transform;
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

	virtual void SetDrawMode(RModel_Mesh::MESH_DRAWMODE mode) = 0;
	//.. include a destructor as well

	//non virtual functions :)
	inline Vector GetPosition()
	{
		if (m_transform)
		{
			return m_transform->m_Position;
		}
		return Vector(0, 0, 0);
	}

	inline MezAngles GetAngles()
	{
		if (m_transform)
		{
			return m_transform->m_Angles;
		}
		return MezAngles(0, 0, 0);
	}

public:
	//defined by the interface

	//Note: This is unused as of now.
	bitfield64_t m_features = 0;
};


//this will never actually be used because if theres no render mode then render functions wont even be called.. but there still needs a class and function bodies since c++
//wont let you create instances of abstract classes which is fair
class RInterface_Null : public RInterface
{
	
};

#endif