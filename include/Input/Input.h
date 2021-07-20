#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <windows.h>
#include "../Debug.h"

namespace WG
{
enum class KEY_STATE : std::uint8_t
{
    KEY_UP,
    KEY_DOWN,
    KEY_PRESS,
    KEY_REALASE
};

class Input
{
    public:
        Input();
        virtual ~Input();

        bool Update(HWND _hWnd);
        KEY_STATE CheckKey(int key) {return keys[prevBuffer][key];}
        bool GetMousePos(int& x, int& y);
        bool GetNormalizeMousePos(float& x, float& y);
        bool GetMouseDelta(int& x, int& y);
        bool GetNormalizeMouseDelta(float& x, float& y);

    protected:
        int actualBuffer;
        int prevBuffer;
        int mouseX;
        int mouseY;
        int mousePrevX;
        int mousePrevY;
        float normMouseX;
        float normMouseY;
        float normMousePrevX;
        float normMousePrevY;
        KEY_STATE keys[2][256];

};
}

#endif // INPUT_H
