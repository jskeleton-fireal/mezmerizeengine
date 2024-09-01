#pragma once
#include "../merize.h"
#include "MRenderable.h"


#define NUMBER_OF_RENDERABLE_SYSTEMS 1

//this is the minimum amount of space allocated per system. defaults to 30
#define DEFAULT_RENDERABLES_SIZE 30


struct MRenderableHandle;
class Engine;
class RenderSystem
{
	friend class MRenderable;
	friend class Engine;
	
private:

	
	typedef stdvector<MRenderableRSHandle> RenderableVector;
	struct RSRenderableSystem {
		//im not sure about the performance of this system, an array would obviously be much faster but the memory issues and clear limits are kind of lame
		
		RenderableVector renderables;
		int m_defsize;
		void render_single();
		bool available();

		RSRenderableSystem(int default_size = DEFAULT_RENDERABLES_SIZE) { m_defsize = default_size; }
	};
private:
	RSRenderableSystem systems[NUMBER_OF_RENDERABLE_SYSTEMS] = { RSRenderableSystem() };
public:
	RSRenderableSystem* operator [] (int i);
private:
	void Render_CallThisInEnginePlease();
	void Render();
	void Engine_Setup(void* window);
};
