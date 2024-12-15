#include "MRenderable.h"
#include "RenderSystem.h"
#include "../staticdefs.h"
#include "rinterface/rinterface_def.h"
#include "model.h"
#include "mdlcache.h"
//called before draw


void MRenderable::SetModel_Id(int model_id)
{
	//this sucks
	//SetModel(engine->cache.m_models[model_id]);
}
void MRenderable::SetModel_Name(const char* model_name)
{
	SetModel(engine->cache.get(CachedStuffManager::nameRModel)->Lookup_Dynamic<RModel>(model_name));
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
	m_rInterface->RegenerateProgram();
	m_rInterface->UploadShader_Vertex("fallback");
	m_rInterface->UploadShader("fallback");
	m_rInterface->UploadTexture_Name("fallback");
	m_rInterface->LinkShaderProgram();
	m_rInterface->UploadVerts(m_model->GetVerts(), m_model->GetVertCount());
	if (m_model->HasNormals())
	{
	m_rInterface->UploadNormals(m_model->GetNormals(), m_model->GetVertCount());
	}	
	if (m_model->GetUVs())
	{
	m_rInterface->UploadUVs(m_model->GetUVs(), m_model->GetVertCount());
	}
	m_rInterface->SetDrawMode((RModelMeshSingle::MESH_DRAWMODE)m_model->GetDrawMode());

	//add to renderables list if not there yet.
	//NOTE: need to do this AFTER. AFTER!!
	if (!m_initialized) { Upload(); }
}

int MRenderable::PrecacheModel_Name(const char* model_name)
{
	CachedStuff_RModels* cache = static_cast<CachedStuff_RModels*>(engine->cache.get(CachedStuffManager::nameRModel));
	int i;
	bool exists = engine->cache.get(CachedStuffManager::nameRModel)->Exists(model_name, &i);
	if (exists) return 1;
	cache->Upload(model_name, RModel::LoadModelFromFile(model_name, 0));
	return 0;
}

