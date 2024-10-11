#pragma once
#include "../merize.h"


//todo: need to move shaders into models. or at least give the models some control

//abstract
class RModel_Base
{
public:
	bool m_valid = 1;
	bool m_expected_deallocation = 0; //is this unused?
	short m_id;
	stdstring m_name;

	virtual bool is_valid() { return m_valid; }

	//probably need to move these into an individual mesh thing but idk
	virtual Vector* GetVerts() = 0;
	virtual int GetVertCount() = 0;	
	virtual int GetMeshCount() { return is_valid(); }
	virtual Vector* GetVerts(int f_mesh_index) { if (!f_mesh_index) return GetVerts();  return 0; }
	virtual int GetVertCount(int f_mesh_index) { if (!f_mesh_index) return GetVertCount(); return 0; }
	virtual int GetDrawMode(int f_mesh_index = 0) { return 4; }

	virtual bool HasNormals() { return false; }
	virtual Vector* GetNormals() = 0;
protected:
	RModel_Base() {}
};


