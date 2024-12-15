#pragma once

#include "texenums.h"
typedef unsigned char byte;

//high level representation of a texture
class RTextureBase
{
public:
	int m_Width = -1;
	int m_Height = -1;
	unsigned short m_flags = 0;
	int m_id = -1; //holdover. may be removed

	virtual int get_bpp();
	virtual tex::TextureFormat get_format();
	virtual void free() = 0;
	virtual byte* get_texture() = 0;

	bool is_point();
	bool dont_create_mips();
	RTextureBase() {};
protected:
};