#pragma once
#include <mez/merize/merize.h>
#include "cmd.h"

class ConBall
{
public:
	struct conball_single_t
	{
		ConsoleThing* thing;
	};
private:
	stdvector<conball_single_t> m_tings;
public:

	void append(ConsoleThing* f_);
	void unpack();

	void kill();
	~ConBall() { kill(); }
};
