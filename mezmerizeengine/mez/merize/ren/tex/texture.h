#pragma once
#include "texrawformats.h"
#include "texturebase.h"
//high level representation of a texture
class RTexture : public RTextureBase
{
	typedef union { byte* raw; tex::RGB8RawTexture rgb; tex::RGBA8RawTexture rgba; } RawTexture;
public:
	tex::TextureFormat m_Format = (tex::TextureFormat)1;
	RawTexture m_rawtexture = {0};
	template <class T>
	T* texture_as_type() { return static_cast<T*>(m_rawtexture); }	
	template <class T>
	T texture_as_typedr() { return static_cast<T>(m_rawtexture); }
	virtual int get_bpp();

	static RTexture* CreateRGBA8Texture(int f_width, int f_height);
	static RTexture* CreateRGBA8Texture(int f_width, int f_height,MezColor f_fillcolor);
	
	virtual void free();
	virtual tex::TextureFormat get_format() { return m_Format; }

	virtual byte* get_texture() { return m_rawtexture.raw; }

	RTexture() {};
protected:
	//create an empty texture
	static RTexture* CreateTexture(int f_width, int f_height, tex::TextureFormat f_format = (tex::TextureFormat)1);

	tex::RGB8RawTexture getRGB8() const { return m_rawtexture.rgb; }
	tex::RGBA8RawTexture getRGBA8() const { return m_rawtexture.rgba; }
};