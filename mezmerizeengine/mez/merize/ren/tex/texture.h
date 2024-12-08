#pragma once
#include "texrawformats.h"

//high level representation of a texture
class RTexture
{
public:
	enum TextureFormat
	{
		RGB8, //(r:8 g:8 b:8)
		RGBA8 //^ with alpha a:8
	};
	enum RTextureFlags //Valid Range is 0 -> 15
	{
		point_filter = (1<<0),
		no_mips = (1<<1),
	};
	typedef union { byte* raw; tex::RGB8RawTexture rgb; tex::RGBA8RawTexture rgba; } RawTexture;
public:
	TextureFormat m_Format = RGBA8;
	int m_Width = -1;
	int m_Height = -1;
	unsigned short m_flags = 0;
	int m_id = -1; //holdover. may be removed
	RawTexture m_rawtexture = {0};
	template <class T>
	T* texture_as_type() { return static_cast<T*>(m_rawtexture); }	
	template <class T>
	T texture_as_typedr() { return static_cast<T>(m_rawtexture); }
	int get_bpp();

	static RTexture* CreateRGBA8Texture(int f_width, int f_height);
	static RTexture* CreateRGBA8Texture(int f_width, int f_height,MezColor f_fillcolor);
	
	void free();

	bool is_point() { return m_flags & point_filter; }
	bool dont_create_mips() { return (m_flags & no_mips); }
	RTexture() {};
protected:
	//create an empty texture
	static RTexture* CreateTexture(int f_width, int f_height, TextureFormat f_format = RGBA8);

	tex::RGB8RawTexture getRGB8() const { return m_rawtexture.rgb; }
	tex::RGBA8RawTexture getRGBA8() const { return m_rawtexture.rgba; }
};