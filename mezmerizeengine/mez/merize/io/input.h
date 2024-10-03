#pragma once

#include "mezkeycode.h"


//standard keyboard / mouse input
static class Input
{
public:
	static bool KeyPressed(MezKeyCode key);
	static bool KeyHeld(MezKeyCode key);
};