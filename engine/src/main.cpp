#include <windows.h>
#include <chrono>
#include "window.h"
#include "appLoop.h"
#include "DirectX12/dxgiFactory.h"
#include "Pipeline/renderer.h"

int main() {
    HINSTANCE hInst = GetModuleHandleW(nullptr);

    wchar_t* title = L"Example";
    int width = 1280;
    int height = 720;
    int nCmdShow = SW_SHOW;

    HWND hwnd = createWindow(hInst, title, width, height, nCmdShow);
    if(hwnd == nullptr)
        return -1;

    // Setup DxgiFactory
    IDXGISwapChain3* swapChain = nullptr;
    SetupDxgiFactory(hwnd, &swapChain);

    u_int frames = 0;
    while (PumpMessages()) {
        // process Windows messages
        if (!PumpMessages()) break;

        Render();

        frames++;
        swapChain->Present(1, 0);
    }


    return 0;
}
