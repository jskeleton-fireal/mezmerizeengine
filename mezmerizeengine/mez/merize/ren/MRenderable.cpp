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
	m_rInterface->UploadShader_Vertex("default3d");
	m_rInterface->UploadShader("test");
	m_rInterface->LinkShaderProgram();
	m_rInterface->UploadVerts(m_model->GetVerts(), m_model->GetVertCount());

	//add to renderables list if not there yet.
	//NOTE: need to do this AFTER. AFTER!!
	if (!m_initialized) { Upload(); }
}

