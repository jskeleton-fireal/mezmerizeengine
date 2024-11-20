#pragma once
#include "../merize.h"
#include "MRenderableBase.h"

class RenderSystem;
class RInterface;
class RModel_Base;

//variant of MRenderableBase that uses the RModel system.
//This is the best general purpose renderable.

//todo: need to add multiple model support per mrenderable thing gigiosdghsdioh
class MRenderable : public MRenderableBase
{
	friend class RenderSystem;
public:
	RModel_Base* m_model = 0;
public:
	//need these to be seperate since numbers are pointer ambiguous (SetModel(0) means id 0 or null string?)
	virtual void SetModel_Id(int model_id);
	virtual void SetModel_Name(const char* model_name);
	virtual void SetModel(RModel_Base* model);

	//0 = okay. 1 = already precached. -1 = failed.
	virtual int PrecacheModel_Name(const char* model_name);
public:
	explicit operator MRenderableRSHandle() { return MRenderableRSHandle(this); }
};

