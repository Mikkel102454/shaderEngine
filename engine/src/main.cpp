#include <windows.h>
#include <chrono>
#include "window.h"
#include "appLoop.h"
#include "DXWindow.h"

int main() {
    HINSTANCE hInst = GetModuleHandleW(nullptr);

    const wchar_t* title = L"Example";
    int width = 1280;
    int height = 720;
    int nCmdShow = SW_SHOW;

    DXWindow window;
    if(!window.Init(hInst, title, width, height, nCmdShow))
        return -1;

    u_int frames = 0;
    while (PumpMessages()) {
        // process Windows messages
        if (!PumpMessages()) break;

        window.Render();

        frames++;
    }

    return 0;
}