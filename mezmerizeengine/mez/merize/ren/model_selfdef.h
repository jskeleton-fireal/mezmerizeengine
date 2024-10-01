#pragma once

#include "model_base.h"
#include "model_mesh.h"

//a 'custom' rmodel

class RModel_SelfDef : public RModel_BaseMesh
{
public:
	//Stores m_verts internally
	Vector* m_verts = 0;

	//VERTS MUST BE ON HEAP!!
	void SelfDef_Create(Vector* f_verts_must_be_on_heap, int count);
	void SelfDef_SetDrawmode(RModel_Mesh::MESH_DRAWMODE f_draw_mode);
	void SelfDef_SetDrawmode(int f_draw_mode) { SelfDef_SetDrawmode((RModel_Mesh::MESH_DRAWMODE)f_draw_mode); }

	~RModel_SelfDef()
	{
		delete[] m_verts;
	}
};