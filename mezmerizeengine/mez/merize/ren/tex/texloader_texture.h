#pragma once
#include "texture.h"

//rtexture that was loaded from texloader
class RTexture_TexLoaded : public RTextureBase
{
public:
	byte* m_data;
	int m_bpp;

	virtual inline void free()
	{
		delete[] m_data;
	}
	virtual inline byte* get_texture()
	{
		return m_data;
	}
	inline virtual int get_bpp()
	{
		return m_bpp;
	}
};