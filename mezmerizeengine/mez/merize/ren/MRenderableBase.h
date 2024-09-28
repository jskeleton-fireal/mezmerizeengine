#pragma once
#include "../merize.h"

//base renderable class
//This is the class that gets stored in the engine's renderable vector. 
class RenderSystem;
class RInterface;
class RModel;
class MRenderableBase;
//(For RenderSystem)
//need to prevent vectors from deallocating renderables because that destroys everything

//you may think: hm why not just call render funcs in the classes that use them NO!!! that 
//note: this may not be needed... not sure abt this one
struct MRenderableRSHandle
{
public:
	MRenderableBase* m_ = 0;
	MRenderableRSHandle(MRenderableBase* f_) { m_ = f_; }
	//some operators
	bool operator !() { return !m_; }
	inline MRenderableBase* get() { return m_; }
	bool operator ==(MRenderableBase* f_) { return m_ == f_; }
};

class MRenderableBase
{
	friend class RenderSystem;
public:
	//Cannot use a unique ptr here beause this is an incomplete type on its own
	RInterface* m_rInterface = 0;
public:
	//call this on create
	virtual void Create();
	//called before draw
	virtual void Prepare();
	//called on draw!
	virtual void Draw();
	//called after draw. 
	virtual void PostDraw();
	//which renderable array are we a part of? later id = gets drawn later
	virtual int DesignatedSystem() { return 0; }

	virtual void RenderSys_Cycle()
	{
		if (!m_visible) return;
		Prepare();
		Draw();
		PostDraw();
	}
	//need to free rInterface member
	~MRenderableBase();

	MRenderableBase()
	{
		Create();
	}

	bool m_visible = 0;
	bool m_initialized = 0;
	bool m_expecteddeallocation = 0;
protected:
	debugvar(bool  m_Ready); //for debugging
	void Upload();
	bool RequestRemoval();
public:
	explicit operator MRenderableRSHandle() { return MRenderableRSHandle(this); }
};