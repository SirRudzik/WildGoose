#include "../Input/Input.h"

WG::Input::Input():
    actualBuffer(1),
    prevBuffer(0),
    mouseX(0),
    mouseY(0),
    mousePrevX(0),
    mousePrevY(0),
    normMouseX(0),
    normMouseY(0),
    normMousePrevX(0),
    normMousePrevY(0)
{
    for(int i = 0; i < 256; i++)
    {
        keys[actualBuffer][i] = WG::KEY_STATE::KEY_UP;
        keys[prevBuffer][i] = WG::KEY_STATE::KEY_UP;
    }
}

WG::Input::~Input()
{
}

bool WG::Input::Update(HWND _hWnd)
{
    for(int i = 0; i < 256; i++)
    {
        int temp = GetAsyncKeyState(i);
        if( temp & 0x8000)
        {
            keys[actualBuffer][i] =
            (keys[prevBuffer][i] == KEY_STATE::KEY_UP || keys[prevBuffer][i] == KEY_STATE::KEY_REALASE ? KEY_STATE::KEY_PRESS : KEY_STATE::KEY_DOWN);
        }
        else
        {
            keys[actualBuffer][i] =
            (keys[prevBuffer][i] == KEY_STATE::KEY_DOWN || keys[prevBuffer][i] == KEY_STATE::KEY_PRESS ? KEY_STATE::KEY_REALASE : KEY_STATE::KEY_UP);
        }
    }
    int temp = actualBuffer;
    actualBuffer = prevBuffer;
    prevBuffer = temp;

    mousePrevX = mouseX;
    mousePrevY = mouseY;
    POINT pos;
    GetCursorPos(&pos);
    ScreenToClient(_hWnd, &pos);
    mouseX = pos.x;
    mouseY = pos.y;
    RECT rect;
    GetClientRect(_hWnd, &rect);
    int height = rect.bottom - rect.top;
    int width = rect.right - rect.left;
    normMouseX = (pos.x * (2.0f / width)) - 1.0f;
    normMouseY = (pos.y * (-2.0f / height)) + 1.0f;
    return true;
}

bool WG::Input::GetMousePos(int& x, int& y)
{
    x = mouseX;
    y = mouseY;
    return true;
}

bool WG::Input::GetNormalizeMousePos(float& x, float& y)
{
    x = normMouseX;
    y = normMouseY;
    return true;
}

bool WG::Input::GetMouseDelta(int& x, int& y)
{
    x = mouseX - mousePrevX;
    y = -(mouseY - mousePrevY);
    return true;
}

bool WG::Input::GetNormalizeMouseDelta(float& x, float& y)
{
    x = normMouseX - normMousePrevX;
    y = normMouseY - normMousePrevY;
    return true;
}

