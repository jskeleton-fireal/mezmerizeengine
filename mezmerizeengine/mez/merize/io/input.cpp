#include "input.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "mez/merize/merize.h"
#include "mez/merize/engine/baseengine.h"
#include <mez/merize/console/cmd.h>

#define mezkeycode_search 0

#if mezkeycode_search
ConsoleVariableBool keycode_search("i_ksrc",0,0);
#else
static bool keycode_search = 0;
#endif

static Vector2 mpos_last = Vector2(0,0);
static bool cursor_locked = false;
static bool focus = true;
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

static bool should_be_accepting_input()
{
    return focus;
}

bool Input::KeyPressed(MezKeyCode key)
{
    return helper.pressed(key);
}

bool Input::KeyHeld(MezKeyCode key)
{
    return helper.held(key);
}

float Input::KeyFWAxis(MezKeyCode forward_key, MezKeyCode backward_key)
{
    bool fw = KeyHeld(forward_key);
    bool bw = KeyHeld(backward_key);
    if (fw == bw) return 0.0f;
    return fw ? 1.0f : -1.0f;
}

Vector2 Input::GetMousePos()
{
    sf::Vector2i i = sf::Mouse::getPosition();
    return { (float)i.x,(float)i.y };
}

Vector2 Input::GetMousePos_Normalized()
{
    if (!should_be_accepting_input()) return mpos_last;
    Vector2 p = GetMousePos();
    return p / engine->rendersys.ViewportSize();
}

Vector2 Input::GetMousePos_Normalized_Delta()
{
    return mpos_last - GetMousePos_Normalized();
}

void Input::CursorLock(bool val)
{
    engine->cursorlock_status(&val);
    cursor_locked = val;
}

bool Input::CursorIsLocked()
{
    return cursor_locked;
}


void Input::notify_key_pressed(MezKeyCode key)
{
    if (!should_be_accepting_input()) return;
    if (keycode_search)
    {
        console_printf("%x (%i) was pressed\n", key, key);
    }

    assert(key <= input_helper::tracking && key >= 0);
    helper.set_pressed(key);
}

void Input::notify_key_released(MezKeyCode key)
{
    if (!should_be_accepting_input()) return;
    assert(key <= input_helper::tracking && key >= 0);
    helper.set_released(key);
}

void Input::tic()
{
    helper.tic_ifneeded();

}

void Input::post_tic()
{
    if (!should_be_accepting_input()) return;
    if (!cursor_locked)
    {
        mpos_last = GetMousePos_Normalized();
    }
    else {
        mpos_last = GetMousePos_Normalized();
        engine->set_mousepos(engine->rendersys.ViewportSize() / 2.0f);
        bool escape_pressed = KeyPressed(MKC_Escape);
        if (escape_pressed)
        {
            //disable cursor lock
            console_printf("cursor has been unlocked\n");
            CursorLock(0);
        }
    }
}

void Input::notify_focus(bool yn)
{
    focus = yn;
}




u8 input_helper::getvalue(int id)
{
    return keys_pressed[id];
}

void input_helper::tic()
{
    if (!should_be_accepting_input()) return;
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
