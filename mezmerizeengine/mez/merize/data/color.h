#pragma once
#include <mez/merize/merize.h>

struct MezColorF
{
	float data[4];
};

struct MezColor
{
	u8 r = 0x0;
	u8 g = 0x0;
	u8 b = 0x0;
	u8 a = 0xff;

	MezColor() = default;

	MezColor(const u8& r, const u8& g, const u8& b, const u8& a)
		: r(r), g(g), b(b), a(a)
	{
	}	
	MezColor(const u8& r, const u8& g, const u8& b)
		: r(r), g(g), b(b), a(0xff)
	{
	}	
	MezColor(const int hexcode)
	{
		//note: you COULD probably do a reintrp cast here to set the hexcode directly.. but im not sure about endian stuff issues
		r = (hexcode & 0xff0000) >> 0x10;
		g = (hexcode & 0x00ff00) >> 0x8;
		b = (hexcode & 0x0000ff) >> 0x0;
		a = 0xff;
	}

	MezColorF Float()
	{
		MezColorF f = MezColorF();
		f.data[0] = r / 255.0f;
		f.data[1] = g / 255.0f;
		f.data[2] = b / 255.0f;
		return f;
	}
};