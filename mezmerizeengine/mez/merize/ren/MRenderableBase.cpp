#include "MRenderableBase.h"
#include "RenderSystem.h"
#include "../staticdefs.h"
#include "rinterface/rinterface_def.h"

void MRenderableBase::Create()
{
	m_rInterface = engine->create_rinterface_instance();
	m_rInterface->Initialize();
}

inline void MRenderableBase::Prepare()
{
	setdebugvar(m_Ready, 1); 
	
	m_rInterface->Prepare();
}

void MRenderableBase::Draw()
{
	//todo: there has got to be a faster way to do this
	m_rInterface->Draw();
}

//called after draw. 

inline void MRenderableBase::PostDraw() { setdebugvar(m_Ready, 0); m_rInterface->PostDraw(); }

//note: what about the model? if its a custom model should we delete it?
MRenderableBase::~MRenderableBase()
{
	delete m_rInterface;
	m_rInterface = 0;
	printf("deallocated the m_rinterface\n");
}

//push this to the rendersys
void MRenderableBase::Upload()
{
	assert(!m_initialized);
	RenderSystem* system = &engine->rendersys;
	system->operator[](DesignatedSystem())->renderables.push_back(this);
	m_initialized = 1;
}

bool MRenderableBase::RequestRemoval()
{
	assert(m_initialized);
	assert(DesignatedSystem() < NUMBER_OF_RENDERABLE_SYSTEMS);
	RenderSystem* system = &engine->rendersys;
	stdvec_removeselection(system->operator[](DesignatedSystem())->renderables, this);
	m_initialized = 0;
	return 1;
}
