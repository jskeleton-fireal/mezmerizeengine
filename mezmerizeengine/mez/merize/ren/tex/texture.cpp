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

RTexture RTexture::CreateRGBA8Texture(int f_width, int f_height)
{
	RTexture tex = CreateTexture(f_width,f_height);
	return tex;
}

RTexture RTexture::CreateRGBA8Texture(int f_width, int f_height, MezColor f_fillcolor)
{
	RTexture tex = CreateTexture(f_width, f_height);
	int colors = f_width * f_height;
	const int bytesize = tex.get_bpp() / 8;

	//This is untested. Hopefully this doesnt corrupt the heap :)
	for (int i = 0; i < colors / 4; i++)
	{
		memcpy(&tex.m_rawtexture.raw + (i * bytesize), &f_fillcolor, sizeof(MezColor));
	}

	return tex;
}

RTexture RTexture::CreateTexture(int f_width, int f_height, TextureFormat f_format)
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
