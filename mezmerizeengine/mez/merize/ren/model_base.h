#pragma once
#include "../merize.h"

//abstract
class RModel_Base
{
public:
	bool m_valid = 1;
	bool m_expected_deallocation = 0; //is this unused?
	short m_id;
	stdstring m_name;

	virtual bool is_valid() { return m_valid; }

	virtual Vector* GetVerts() = 0;
	virtual int GetVertCount() = 0;
protected:
	RModel_Base() {}
};


