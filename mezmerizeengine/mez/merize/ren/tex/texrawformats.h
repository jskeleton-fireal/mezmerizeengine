#pragma once
#include <mez/merize/data/color.h>
typedef unsigned char byte;
namespace tex
{
	typedef MezColor *RGBA8RawTexture;
	typedef struct { byte r; byte g; byte b; } *RGB8RawTexture;
}