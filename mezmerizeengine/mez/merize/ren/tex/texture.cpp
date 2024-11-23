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

RTexture* RTexture::CreateRGBA8Texture(int f_width, int f_height)
{
	RTexture* tex = CreateTexture(f_width,f_height);
	return tex;
}

RTexture* RTexture::CreateRGBA8Texture(int f_width, int f_height, MezColor f_fillcolor)
{
	RTexture* tex = CreateTexture(f_width, f_height);
	int colors = f_width * f_height;
	const int bytesize = 4;
	memset(tex->m_rawtexture.raw, 0x55, colors * bytesize);
	//This is untested. Hopefully this doesnt corrupt the heap :)
	for (int i = 0; i < colors; i+=4)
	{
		memcpy(tex->m_rawtexture.raw + (i), &f_fillcolor, sizeof(MezColor));
	}

	return tex;
}

void RTexture::free()
{
	delete[] m_rawtexture.raw;
}

RTexture* RTexture::CreateTexture(int f_width, int f_height, TextureFormat f_format)
{
	RTexture* texture = new RTexture();
	texture->m_Format = f_format;
	int bpp = texture->get_bpp();
	assert_msg(!(bpp % 8), "bpp must be divisible by 8");
	int size = f_width * f_height * (bpp / 8);
	texture->m_rawtexture.raw = new byte[size];
	texture->m_Height = f_height;
	texture->m_Width = f_width;
	return texture;
}
