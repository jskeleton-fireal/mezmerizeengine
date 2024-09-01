#include "RenderSystem.h"
#include "rinterface/rinterface_def.h"
#include "../Engine.h"

//prevents rendering when no renderables exist
#define RENDER_OPTIMIZATION 1

//need to allocate a minimum amount 

RenderSystem::RSRenderableSystem* RenderSystem::operator[](int i)
{
	//only reason this is overloaded LOL
	assert(i < NUMBER_OF_RENDERABLE_SYSTEMS);
	return &systems[i];
}

void RenderSystem::Render_CallThisInEnginePlease()
{
	Render();
}
void RenderSystem::Render()
{
#if RENDER_OPTIMIZATION
	bool should_render = false;
	for (int i = 0; i < NUMBER_OF_RENDERABLE_SYSTEMS; i++)
	{
		should_render = systems[i].available();
		if (should_render) break;
	}
	if (!should_render) return; //dont render
#endif

	RInterface_Default::Static_BeforeRender(engine->m_Window);
	for (int i = 0; i < NUMBER_OF_RENDERABLE_SYSTEMS; i++)
	{
		systems[i].render_single();
	}
	RInterface_Default::Static_AfterRender(engine->m_Window);
}

void RenderSystem::Engine_Setup(void* window)
{
	RINTERFACE_WINDOW_CLASS* win = reintrp(window, RINTERFACE_WINDOW_CLASS*);
	RInterface_Default::Static_InitializeWindow(win);
}

void RenderSystem::RSRenderableSystem::render_single()
{
	if (renderables.capacity() < m_defsize)
	{
		renderables.reserve(m_defsize);
	}
	for (int i = 0; i < renderables.size(); i++)
	{
		assert(renderables[i]);
		renderables[i].get()->Prepare();
		renderables[i].get()->Draw();
		renderables[i].get()->PostDraw();
	}
}

bool RenderSystem::RSRenderableSystem::available()
{
	return renderables.size();
}
