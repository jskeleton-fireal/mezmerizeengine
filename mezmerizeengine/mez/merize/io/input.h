#pragma once

#include "mezkeycode.h"


//standard keyboard / mouse input
static class Input
{
	friend class BaseEngine;
public:
	static bool KeyPressed(MezKeyCode key);
	static bool KeyHeld(MezKeyCode key);

	//returns 1.0 <-> -1.0. for when you need one key to be forward, and one to be backwards.
	//intended to be a temporary solution! thsi will be replaced with a key bindings system at some point (I will keep this for debugging purposes btw)
	static float KeyFWAxis(MezKeyCode forward_key, MezKeyCode backward_key);
private:
	static void notify_key_pressed(MezKeyCode key);
	static void notify_key_released(MezKeyCode key);
	static void tic();
};