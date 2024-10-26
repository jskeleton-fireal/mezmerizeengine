#include "rinterface.h"

void RInterface::KillTemplate()
{
	delete m_template;
	m_template = 0;
}

void RInterface::InvalidateTemplate()
{
	m_template->Invalidate(this);
}
