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
	typedef union { byte* raw; tex::RGB8RawTexture rgb; tex::RGBA8RawTexture rgba; } RawTexture;
public:
	TextureFormat m_Format;
	int m_Width;
	int m_Height;
	//not used.. planning on adding point filtering to this 
	unsigned short m_flags;
	RawTexture m_rawtexture;
	template <class T>
	T* texture_as_type() { return static_cast<T*>(m_rawtexture); }	
	template <class T>
	T texture_as_typedr() { return static_cast<T>(m_rawtexture); }
	int get_bpp();

	static RTexture CreateTexture(TextureFormat f_format, int f_width, int f_height);
protected:
	RTexture() {};
	~RTexture();
};