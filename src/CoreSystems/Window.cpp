#include "Window.h"

WG::Window::Window(const char* _name, int _width, int _height, DWORD _style):
    hWnd(NULL),
    isActive(false),
    isClose(false),
    height(_height),
    width(_width),
    style(_style),
    name(_name)
{
    #ifdef WG_DEBUG
    std::cout << "Window::Konstruktor \n";
    #endif
    //ctor
}

WG::Window::~Window()
{
    #ifdef WG_DEBUG
    std::cout << "Window::Destruktor \n";
    #endif
    //dtor
}

///////////////////////////////////////////////////////////////////////////////////////////

bool WG::Window::Init()
{
    #ifdef WG_DEBUG
    std::cout << "Window::Init->Start \n";
    #endif

    WNDCLASSEX winCl;

    winCl.hInstance = GetModuleHandle(NULL);
    winCl.lpszClassName = "WG::Window";
    winCl.lpfnWndProc = WndProc;
    winCl.style = 0;
    winCl.cbSize = sizeof(WNDCLASSEX);
    winCl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winCl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    winCl.hCursor = LoadCursor(NULL, IDC_ARROW);
    winCl.lpszMenuName = NULL;
    winCl.cbClsExtra = 0;
    winCl.cbWndExtra = 0;
    winCl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    #ifdef WG_DEBUG
    std::cout << "Window::Init->Window Class Register \n";
    #endif

    if(!RegisterClassEx(&winCl))
    {
        std::cout << "Niezarejestrowano klasy okna" << std::endl;
    }

    RECT windowRect;
    windowRect.left = 0;
    windowRect.right = width;
    windowRect.bottom = height;
    windowRect.top = 0;

    AdjustWindowRect(&windowRect, style, false);

    #ifdef WG_DEBUG
    std::cout << "Window::Init->Window Create \n";
    #endif

    hWnd = CreateWindowEx(0,
                          "WG::Window",
                          name,
                          style,
                          400,
                          200,
                          windowRect.right - windowRect.left,
                          windowRect.bottom - windowRect.top,
                          NULL,
                          NULL,
                          GetModuleHandle(NULL),
                          NULL);
    if(hWnd == NULL)
    {
        std::cout << "Nie utwozono okna" << std::endl;
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow(hWnd, SW_NORMAL);
    UpdateWindow(hWnd);

    #ifdef WG_DEBUG
    std::cout << "Window::Init->End \n";
    #endif

    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int WG::Window::CheckEvent()
{
    #ifdef WG_DEBUG
    std::cout << "Window::CheckEvent->Start \n";
    #endif

    MSG Komunikat;
    if( PeekMessage(&Komunikat, NULL, 0, 0, PM_REMOVE) )
    {
        TranslateMessage(&Komunikat);
        DispatchMessage(&Komunikat);
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
bool WG::Window::EnableGL()
{
    #ifdef WG_DEBUG
    std::cout << "Window::EnableGL\n";
    #endif

    PIXELFORMATDESCRIPTOR pfd{0};

    int format;

    hDC = GetDC(hWnd);

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    format = ChoosePixelFormat(hDC, &pfd);

    SetPixelFormat(hDC, format, &pfd);

    Hglrc = wglCreateContext(hDC);

    wglMakeCurrent(hDC, Hglrc);
    glewInit();

    glViewport(0, 0, width, height);

    return true;
}

bool WG::Window::DisableGL()
{
    #ifdef WG_DEBUG
    std::cout << "Window::DisableGL\n";
    #endif

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(Hglrc);
    ReleaseDC(hWnd, hDC);
    return true;
}

bool WG::Window::SwapBuffer()
{
    #ifdef WG_DEBUG
    std::cout << "Window::SwapBuffer\n";
    #endif

    SwapBuffers(hDC);
    return true;
}

bool WG::Window::Close()
{
    SendMessage(hWnd, WM_CLOSE, 0, 0);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WG::Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    #ifdef WG_DEBUG
    std::cout << "WndProc" << std::endl;
    #endif

    Window* pWindow = nullptr;
    pWindow = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    return pWindow->RealProc(hWnd, message, wParam, lParam);
}

LRESULT WG::Window::RealProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    #ifdef WG_DEBUG
    std::cout << "RealWndProc" << std::endl;
    #endif

    bool result = false;
    switch(message)
    {
    case WM_DESTROY:
        result = OnDestroy();
        break;

    case WM_CLOSE:
        result = OnClose();
        break;

    case WM_ACTIVATE:
        result = OnActivate(wParam);
        break;

    case WM_ENTERSIZEMOVE:
        result = OnEnterSizeMove();
        break;

    case WM_EXITSIZEMOVE:
        result = OnExitSizeMove();
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    if(result)
        return 0;
    else
        return DefWindowProc(hWnd, message, wParam, lParam);
}

bool WG::Window::OnCreate(){return false;}

bool WG::Window::OnClose()
{
    isClose = true;
    return true;
}

bool WG::Window::OnDestroy()
{
    DisableGL();
    PostQuitMessage(0);
    return true;
}
bool WG::Window::OnSize(WPARAM wParam, LPARAM lParam){return false;}

bool WG::Window::OnActivate(WPARAM wParam)
{
    isActive = LOWORD(wParam) == WA_INACTIVE ? false : true;
    return true;
}

bool WG::Window::OnEnterSizeMove()
{
    return false;
}

bool WG::Window::OnExitSizeMove()
{
    return false;
}
