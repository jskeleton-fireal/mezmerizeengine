#pragma once

#include "propbase.h"

class PropertyContainer
{
public:
	std::vector<PropBase*> m_props;

	void push_back(PropBase* i)
	{
		m_props.push_back(i);
	}

	~PropertyContainer()
	{
		for (int i = 0; i < m_props.size(); i++)
		{
			delete m_props.at(i);
		}
	}

	int size() { return m_props.size(); }
	PropBase* at(int i) { return m_props.at(i); }
	PropBase* operator[](int i) { return at(i); }
};