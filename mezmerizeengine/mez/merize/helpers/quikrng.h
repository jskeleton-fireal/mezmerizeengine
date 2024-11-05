#pragma once


//simple xor shift
short quikrng16(short x)
{
	//theres a tool reference here somewhere but im not gonna make that joke
	x ^= x << 7;
	x ^= x >> 9;
	x ^= x << 8;
	return x;
}