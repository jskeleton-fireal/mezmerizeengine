#pragma once
//#include "../staticdefs.h"

#include "../merize.h"
#include "model_base.h"
#include "model_mesh.h"

class RModel_Internal;


//handles .obj files and whatnot in the rmodel system

class RModel : public RModel_BaseMesh
{
public:

protected:
	RModel_Internal* m_;
	RModel();
public:
	~RModel();
	void unload_internal();
public:
	static RModel* LoadModelFromFile(const char* filename, bool essential = 0);
};