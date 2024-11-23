#ifndef CACHEDSTUFFMGR_H
#define CACHEDSTUFFMGR_H


#include "CachedStuff.h"
#include "mez/merize/ren/mdlcache.h"
#include "mez/merize/ren/tex/texcache.h"

//This is what is in Engine
class CachedStuffManager
{
public:
	CachedStuff_RModels m_models;
	CachedStuff_RTexture m_textures;
};
#endif