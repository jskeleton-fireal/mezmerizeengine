#include "MRenderable.h"
#include "RenderSystem.h"
#include "../staticdefs.h"
#include "rinterface/rinterface_def.h"
//called before draw


void MRenderable::SetModel_Id(int model_id)
{
	//this sucks
	//SetModel(engine->cache.m_models[model_id]);
}
void MRenderable::SetModel_Name(const char* model_name)
{
	SetModel(engine->cache.m_models.Lookup(model_name));
}
void MRenderable::SetModel(RModel_Base* model)
{
	if (!model)
	{
		m_model = 0;
		m_visible = 0;
		if (m_initialized) RequestRemoval();
		return;
	}
	m_model = model;
	m_visible = 1;

	//Need to regenerate!
	//todo: need to have the model have shaders
	m_rInterface->UploadShader_Vertex("default3d");
	m_rInterface->UploadShader("test");
	m_rInterface->LinkShaderProgram();
	m_rInterface->UploadVerts(m_model->GetVerts(), m_model->GetVertCount());
	if (m_model->HasNormals())
	{
	m_rInterface->UploadNormals(m_model->GetNormals(), m_model->GetVertCount());
	}
	m_rInterface->SetDrawMode((RModel_Mesh::MESH_DRAWMODE)m_model->GetDrawMode());

	//add to renderables list if not there yet.
	//NOTE: need to do this AFTER. AFTER!!
	if (!m_initialized) { Upload(); }
}

int MRenderable::PrecacheModel_Name(const char* model_name)
{
	int i;
	bool exists = engine->cache.m_models.Exists(model_name, &i);
	if (exists) return 1;
	engine->cache.m_models.Upload(model_name, RModel::LoadModelFromFile(model_name, 0));
	return 0;
}

