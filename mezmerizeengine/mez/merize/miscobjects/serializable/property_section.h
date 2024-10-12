#pragma once

#include "propbase.h"

//used to declare a section

class RawPropSection : public PropBase
{
public:
	bool m_end;
	//use 0 for the name to mark the end
	RawPropSection(const char* f_name = 0)
	{
		m_name = f_name;
		m_end = f_name==0;
	}
};