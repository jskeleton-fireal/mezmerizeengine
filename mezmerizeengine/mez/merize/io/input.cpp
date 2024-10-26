#include "input.h"
#include <SFML/Window/Keyboard.hpp>
#include "mez/merize/merize.h"
#include "mez/merize/engine/baseengine.h"
#include <mez/merize/console/cmd.h>

#define mezkeycode_search 0 

//yeah. this sucks. BUT! BUT! a bitmask would use more CPU..
struct input_helper
{
    static const int tracking = 0xff;
    float last_tic = -1;
    u8 keys_pressed[tracking];

    u8 getvalue(int id);
    bool pressed(int id) { return getvalue(id) & 0x10; }
    bool held(int id) { return getvalue(id) & 0x01; }
    bool released(int id) { return getvalue(id) & 0x20; }
    void set_pressed(int id) { if (!keys_pressed[id]) keys_pressed[id] = 0x11; }
    void set_released(int id) { keys_pressed[id] = 0x20; }

    void tic();
    void tic_ifneeded();
};

static input_helper helper;

bool Input::KeyPressed(MezKeyCode key)
{
    return helper.pressed(key);
}

bool Input::KeyHeld(MezKeyCode key)
{
    //not yet
    return helper.held(key);
}

float Input::KeyFWAxis(MezKeyCode forward_key, MezKeyCode backward_key)
{
    bool fw = KeyHeld(forward_key);
    bool bw = KeyHeld(backward_key);
    if (fw == bw) return 0.0f;
    return fw ? 1.0f : -1.0f;
}


void Input::notify_key_pressed(MezKeyCode key)
{
#if mezkeycode_search
    console_printf("%x (%i) was pressed\n", key,key);
#endif
    assert(key <= input_helper::tracking && key >= 0);
    helper.set_pressed(key);
}

void Input::notify_key_released(MezKeyCode key)
{
    assert(key <= input_helper::tracking && key >= 0);
    helper.set_released(key);
}

void Input::tic()
{
    helper.tic_ifneeded();
}




u8 input_helper::getvalue(int id)
{
    return keys_pressed[id];
}

void input_helper::tic()
{
    last_tic = engine->time;
    for (int i = 0; i < input_helper::tracking;i++)
    {
        keys_pressed[i] &= 0x01;
    }
}

void input_helper::tic_ifneeded()
{
    if (last_tic != engine->time) tic();
}
