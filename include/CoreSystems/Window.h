#ifndef WINDOW_H
#define WINDOW_H

#include "../Debug.h"

#include <windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace WG
{
class Window
{
    public:
        Window(const char* _name = "Test", int _width = 600, int _height = 600, DWORD _style = WS_BORDER | WS_SYSMENU | WS_CAPTION);
        virtual ~Window();

        bool Init();
        bool EnableGL();
        bool DisableGL();
        bool SwapBuffer();
        int CheckEvent();
        bool Close();
        bool GetSize(int& _height, int& _width);
        HWND GetHandle() const {return hWnd;}
        bool IsActive() const {return isActive;}
        bool IsClose() const {return isClose;}

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT RealProc(HWND, UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        virtual bool OnCreate();
        virtual bool OnClose();
        virtual bool OnDestroy();
        virtual bool OnSize(WPARAM wParam, LPARAM lParam);
        virtual bool OnActivate(WPARAM wParam);
        virtual bool OnEnterSizeMove();
        virtual bool OnExitSizeMove();

        HWND hWnd;
        bool isActive;
        bool isClose;
        int height;
        int width;
        DWORD style;
        const char* name;
        HGLRC Hglrc;
        HDC hDC;
};
}
#endif // WINDOW_H
