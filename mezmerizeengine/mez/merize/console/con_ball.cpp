#include "con_ball.h"
#include "conhelper.h"
void ConBall::append(ConsoleThing* f_)
{
	m_tings.push_back(conball_single_t(f_));
}

void ConBall::unpack()
{
	for (int i = 0; i < m_tings.size(); i++)
	{
		ConsoleHelper::FindGlobal()->m_things.push_back(m_tings[i].thing);
	}
}

void ConBall::kill()
{

}
