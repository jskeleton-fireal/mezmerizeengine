#ifndef TEXENUMS_H
#define TEXENUMS_H
namespace tex
{
	enum RTextureFlags //Valid Range is 0 -> 15
	{
		point_filter = (1 << 0),
		no_mips = (1 << 1),
	};
	enum TextureFormat
	{
		RGB8, //(r:8 g:8 b:8)
		RGBA8 //^ with alpha a:8
	};
}
#endif