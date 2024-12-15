#pragma once
#include <mez/merize/data/color.h>
typedef u8 byte;
namespace tex
{
	typedef MezColor *RGBA8RawTexture;
	typedef struct { byte r; byte g; byte b; } *RGB8RawTexture;

}
	#include "texenums.h"