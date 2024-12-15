#pragma once
#include <mez/merize/merize.h>
#include "efactory.h"


class EntBall
{
public:
	struct entball_single_t
	{
		efactory_t* thing;
	};
private:
	stdvector<entball_single_t> m_tings;
public:

	void append(efactory_t* f_);
	void unpack();

	void kill();
	~EntBall() { kill(); }
};
