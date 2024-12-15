#define CACHEDSTUFF_GIMMEMORE 1
#include "cachedstuffmgr.h"
#include "mez/merize/ren/mdlcache.h"
#include "mez/merize/ren/tex/texcache.h"

void CachedStuffManager::load()
{
	memset(m_list, 0, sizeof(m_list));
	m_list[nameRModel] = new CachedStuff_RModels();
	m_list[nameRTexture] = new CachedStuff_RTexture();
}

CachedStuffManager::~CachedStuffManager()
{
	for (int i = 0; i < num_of_names; i++)
	{
		delete m_list[i];
	}
}
