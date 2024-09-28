#pragma once


class RModel_Mesh
{
public:
	Vector* m_Verts;
	int m_NumOfVerts;
};

class RModel_BaseMesh : public RModel_Base
{
public:
	//need to set a value here in case this gets destructed without loading a model
	RModel_Mesh* m_meshes = 0;

	~RModel_BaseMesh()
	{
		delete m_meshes;
		m_meshes = 0;
	}
	virtual Vector* GetVerts() { return m_meshes->m_Verts; }
	virtual int GetVertCount() { return m_meshes->m_NumOfVerts; }
protected:
	RModel_BaseMesh() {}
};