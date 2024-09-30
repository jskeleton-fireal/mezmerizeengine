#pragma once


class RModel_Mesh
{
public:
	//this needs to be moved..
	enum MESH_DRAWMODE
	{
		DM_Points = 0,
		DM_Lines = 1,
		DM_Triangles = 4,
		DM_TriangleStrip = 5,
	};
public:
	Vector* m_Verts;
	int m_NumOfVerts;
	u8 m_DrawMode;
};

class RModel_BaseMesh : public RModel_Base
{
public:
	//need to set a value here in case this gets destructed without loading a model
	RModel_Mesh* m_meshes = 0;
	int m_mesh_count;

	~RModel_BaseMesh()
	{
		delete m_meshes;
		m_meshes = 0;
	}
	virtual Vector* GetVerts() { return m_meshes->m_Verts; }
	virtual int GetVertCount() { return m_meshes->m_NumOfVerts; }
	virtual int GetMeshCount() { return m_mesh_count; }
	virtual Vector* GetVerts(int f_mesh_index) { return m_meshes[f_mesh_index].m_Verts; }
	virtual int GetVertCount(int f_mesh_index) { return m_meshes[f_mesh_index].m_NumOfVerts; }
	virtual int GetDrawMode(int f_mesh_index) { return m_meshes[f_mesh_index].m_DrawMode; }

protected:
	RModel_BaseMesh() {}
};