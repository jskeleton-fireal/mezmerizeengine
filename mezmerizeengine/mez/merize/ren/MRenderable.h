#pragma once
#include "../merize.h"
//base renderable class
//This is the class that gets stored in the engine's renderable vector. 
class RenderSystem;
class RInterface;
class RModel;
class MRenderable
{
	friend class RenderSystem;
public:
	//Cannot use a unique ptr here beause this is an incomplete type on its own
	RInterface* m_rInterface = 0;
	RModel* m_model;
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

	//need these to be seperate since numbers are pointer ambiguous (SetModel(0) means id 0 or null string?)
	virtual void SetModel_Id(int model_id);
	virtual void SetModel_Name(const char* model_name);
	virtual void SetModel(RModel* model);

	//need to free rInterface member
	~MRenderable();

	MRenderable()
	{
		Create();
	}

	bool m_visible;
	bool m_initialized;
protected:
	debugvar(bool  m_Ready); //for debugging
	void Upload();
	bool RequestRemoval();
	
};

