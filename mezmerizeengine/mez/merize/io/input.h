#pragma once

#include "mezkeycode.h"

#include <mez/merize/data/mezvector2.h>
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

	//relative to window
	static Vector2 GetMousePos();
	//range 0 - 1 on each axis
	static Vector2 GetMousePos_Normalized();
	static Vector2 GetMousePos_Normalized_Delta();

	static void CursorLock(bool val);
	static bool CursorIsLocked();
private:
	static void notify_key_pressed(MezKeyCode key);
	static void notify_key_released(MezKeyCode key);
	static void tic();
	static void post_tic();

	static void notify_focus(bool yn);
};