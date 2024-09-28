#pragma once
//#include "../staticdefs.h"

#include "../merize.h"

class RModel_Internal;

class RModel_Mesh
{
public:
	Vector* m_Verts;
	int m_NumOfVerts;
};

class RModel
{
public:
	bool m_valid = 1;
	bool m_expected_deallocation = 0; //is this unused?
	short m_id;
	stdstring m_name;
	//need to set a value here in case this gets destructed without loading a model
	RModel_Mesh* m_meshes = 0; 
private:
	RModel_Internal* m_;
	RModel();
public:
	~RModel();
	void unload_internal();
	bool is_valid(){ return m_meshes; }
public:
	static RModel* LoadModelFromFile(const char* filename, bool essential = 0);
};