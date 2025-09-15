#include "window.h"

void OnSize(HWND hwnd, UINT flag, int width, int height);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            OnSize(hwnd, (UINT)wParam, width, height);
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void OnSize(HWND hwnd, UINT flag, int width, int height) {
    //TODO resize logic
}

HWND WINAPI createWindow(HINSTANCE hInstance, wchar_t* title, int width, int height,  int nCmdShow){
    MSG Msg;

    // Register the window class.
    const wchar_t* CLASS_NAME = L"Sample Window Class";

    WNDCLASSEXW wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.cbSize = sizeof(WNDCLASSEXW);

    RegisterClassExW(&wc);

    // Create the window.
    HWND hwnd = CreateWindowExW(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            title,                          // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,

            nullptr,       // Parent window
            nullptr,       // Menu
            hInstance,          // Instance handle
            nullptr        // Additional application data
    );

    if(hwnd != nullptr)
    {
        ShowWindow(hwnd, nCmdShow);
        UpdateWindow(hwnd);
    }

    return hwnd;
}
