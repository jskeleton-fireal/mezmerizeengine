#include "model_selfdef.h"

void RModel_SelfDef::SelfDef_Create(Vector* f_verts_must_be_on_heap, int count)
{
	m_verts = f_verts_must_be_on_heap;
	m_meshes = new RModel_Mesh();
	m_meshes->m_Verts = m_verts;
	m_meshes->m_NumOfVerts = count;
	m_meshes->m_DrawMode = RModel_Mesh::DM_Triangles;
}

void RModel_SelfDef::SelfDef_SetDrawmode(RModel_Mesh::MESH_DRAWMODE f_draw_mode)
{
	m_meshes->m_DrawMode = f_draw_mode;
}
