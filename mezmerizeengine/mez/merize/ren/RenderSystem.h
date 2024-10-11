#pragma once
#include "../merize.h"
#include "MRenderableBase.h"
#include "camera.h"
#include "mez/merize/data/instance_ptr.h"
#include "mez/merize/data/environment.h"


#define NUMBER_OF_RENDERABLE_SYSTEMS 1

//this is the minimum amount of space allocated per system. defaults to 30
#define DEFAULT_RENDERABLES_SIZE 30



struct MRenderableHandle;
class BaseEngine;
class RStatic;
class RenderSystem
{
	friend class MRenderableBase;
	friend class MRenderable;
	friend class BaseEngine;
	
public:
	instance_ptr<environment_sky_t> enviro_sky;
	RStatic* m_rstatic = 0;
	instance_ptr<MezCamera> m_camera;

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
