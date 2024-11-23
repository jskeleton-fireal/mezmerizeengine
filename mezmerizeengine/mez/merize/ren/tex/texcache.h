#pragma once

#include "mez/merize/engine/cachedstuff.h"
#include "texture.h"

class CachedStuff_RTexture : public CachedStuff<RTexture>
{
public:
	CachedStuff_RTexture()
	{

	}
	virtual void CreateDefaults()
	{
		Upload(Fallback(), RTexture::CreateRGBA8Texture(1,1,MezColor(0xffffff)));
	}
	virtual const char* Fallback() { return "blank"; }
	virtual const char* prettyname() { return "texture"; }
};