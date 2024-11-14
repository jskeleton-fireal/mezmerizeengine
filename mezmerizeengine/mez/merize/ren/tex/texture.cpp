#include "texture.h"

int RTexture::get_bpp()
{
	switch (m_Format)
	{
	case TextureFormat::RGB8:
		return 24;
	case TextureFormat::RGBA8:
		return 32;
	}
}

RTexture RTexture::CreateTexture(TextureFormat f_format, int f_width, int f_height)
{
	RTexture texture = RTexture();
	texture.m_Format = f_format;
	int bpp = texture.get_bpp();
	int size = f_width * f_height * (bpp / 8);
	texture.m_rawtexture.raw = new byte[size];
	texture.m_Height = f_height;
	texture.m_Width = f_width;
	return texture;
}

RTexture::~RTexture()
{
	delete[] m_rawtexture.raw;
}
