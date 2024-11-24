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
	virtual void Initialize() {}
	virtual void UploadVerts(Vector verts[],int count = -1) {}
	virtual void UploadNormals(Vector normals[],int count = -1) {}
	virtual void UploadShader_Id(int shader_id) {}
	virtual void UploadShader(const char* shader_id) {}
	virtual void UploadShader_Vertex(const char* shader_id) {}
	virtual void LinkShaderProgram() {}
	virtual void RegenerateProgram() {}
	virtual void Prepare() {} //set schtuff
	virtual void Draw() {}
	virtual void PostDraw() {} //reset stuff set by prepare

	//new
	virtual void UploadTexture(class RTexture* f_texture,int f_index = 0) {}
	virtual void UploadUVs(struct Vector f_uvs[], int f_count) {}
	virtual void UploadTexture_Name(const char* f_name,int f_index = 0) {}


	virtual void SetDrawMode(RModelMeshSingle::MESH_DRAWMODE mode) {}
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
	virtual void RequestFeature(rinterface_feature_t f_feature) {}
	virtual void KillTemplate();
	virtual void InvalidateTemplate();
};

typedef RInterface RInterface_Null;

#endif