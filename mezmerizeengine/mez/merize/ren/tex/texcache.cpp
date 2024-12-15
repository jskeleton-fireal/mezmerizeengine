#include "texcache.h"
#include "texenums.h"
using namespace tex;

RTextureBase* CachedStuff_RTexture::CreateFallback()
{
	MezColor fb_Color1 = MezColor(0xff70ff);
	MezColor fb_Color2 = MezColor(0xa0ffda);
	RTexture* fallbacktex = RTexture::CreateRGBA8Texture(2, 2);
	fallbacktex->m_rawtexture.rgba[0] = fb_Color2;
	fallbacktex->m_rawtexture.rgba[1] = fb_Color1;
	fallbacktex->m_rawtexture.rgba[2] = fb_Color1;
	fallbacktex->m_rawtexture.rgba[3] = fb_Color2;
	fallbacktex->m_flags = point_filter | no_mips;
	return fallbacktex;
}
