#ifndef RINTERFACE
#define RINTERFACE
#include "mez/merize/version.h"
#include "mez/merize/merize.h"
#include "mez/merize/engine/baseengine.h"
#include "mez/merize/ren/rinterface/rtemplate/template.h"
#include "mez/merize/ren/rinterface/rinterface_feature.h"
//rinterfaces are what connect renderables to the render system of choice

namespace sf
{
	class Window;
}
class RModel;


class RInterface
{
public:
	RTemplate* m_template = 0;
	instance_ptr<Transform> m_transform;
	//member
	virtual void Initialize() = 0;
	virtual void UploadVerts(Vector verts[],int count = -1) = 0;
	virtual void UploadNormals(Vector normals[],int count = -1) = 0;
	virtual void UploadShader_Id(int shader_id) = 0;
	virtual void UploadShader(const char* shader_id) = 0;
	virtual void UploadShader_Vertex(const char* shader_id) = 0;
	virtual void LinkShaderProgram() = 0;
	virtual void RegenerateProgram() = 0;
	virtual void Prepare() = 0; //set schtuff
	virtual void Draw() = 0;
	virtual void PostDraw() = 0; //reset stuff set by prepare


	virtual void SetDrawMode(RModelMeshSingle::MESH_DRAWMODE mode) = 0;
	//.. include a destructor as well

	//non virtual functions :)
	inline Vector GetPosition()
	{
		return m_transform.get()->m_Position;
	}

	inline MezAngles GetAngles()
	{
		return m_transform.get()->m_Angles;
	}

	~RInterface()
	{
		delete m_template;
	}

public:
	virtual void RequestFeature(rinterface_feature_t f_feature) = 0;
	virtual void KillTemplate();
	virtual void InvalidateTemplate();
};


//this will never actually be used because if theres no render mode then render functions wont even be called.. but there still needs a class and function bodies since c++
//wont let you create instances of abstract classes which is fair
class RInterface_Null : public RInterface
{
	
};

#endif