#include "MRenderable.h"
#include "RenderSystem.h"
#include "../staticdefs.h"
#include "rinterface/rinterface_def.h"
//called before draw

void MRenderable::Create()
{
	m_rInterface = new RInterface_Default();
	printf("Created an r_interface\n");
}

//Why the fuck doesnt this work. Fuck vectors. Fuck vectors so much.
inline void MRenderable::Prepare() { setdebugvar(m_Ready, 1); m_rInterface->Prepare(); }

void MRenderable::Draw()
{
	//todo: there has got to be a faster way to do this
	if (m_visible)
	m_rInterface->Draw();
}

//called after draw. 

inline void MRenderable::PostDraw() { setdebugvar(m_Ready, 0); m_rInterface->PostDraw(); }
void MRenderable::SetModel_Id(int model_id)
{
	//this sucks
	//SetModel(engine->cache.m_models[model_id]);
}
void MRenderable::SetModel_Name(const char* model_name)
{
	SetModel(engine->cache.m_models.Lookup(model_name));
}
void MRenderable::SetModel(RModel* model)
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
	if (!m_initialized) Upload();
	
}
MRenderable::~MRenderable()
{
	delete m_rInterface;
	m_rInterface = 0;
	printf("deallocated the m_rinterface\n");
}
void MRenderable::Upload()
{
	assert(!m_initialized);
	RenderSystem* system = &engine->rendersys;
	system->operator[](DesignatedSystem())->renderables.push_back(this);
	m_initialized = 1;
}

bool MRenderable::RequestRemoval()
{
	assert(m_initialized);
	assert(DesignatedSystem() < NUMBER_OF_RENDERABLE_SYSTEMS);
	RenderSystem* system = &engine->rendersys;
	stdvec_removeselection(system->operator[](DesignatedSystem())->renderables, this);
	m_initialized = 0;
	return 1;
}
