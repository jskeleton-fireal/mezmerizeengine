#include "ent_ball.h"
#include "efactory_private.h"

void EntBall::append(efactory_t* f_)
{
	assert(f_->m_flags & EFACTORY_FLAGS_EBALL);
	m_tings.push_back(entball_single_t(f_));
	
}

void EntBall::unpack()
{
	for (int i = 0; i < m_tings.size(); i++)
	{
		the_efac_internal.upload(m_tings[i].thing);
	}
}

void EntBall::kill()
{

}
