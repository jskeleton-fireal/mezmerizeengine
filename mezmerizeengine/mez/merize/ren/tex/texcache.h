#pragma once

#include "mez/merize/engine/cachedstuff.h"
#include "texture.h"

class CachedStuff_RTexture : public CachedStuff<RTextureBase>
{
public:
	CachedStuff_RTexture()
	{

	}
	virtual void CreateDefaults();
	virtual const char* Fallback() { return "blank"; }
	virtual const char* prettyname() { return "texture"; }
};