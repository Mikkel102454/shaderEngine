#include "DXWindow.h"

bool DXWindow::Init(HINSTANCE hInstance, const wchar_t* title, int width, int height, int nCmdShow){
    m_width = width;
    m_height = height;

    if(!InitWindow(hInstance, title, width, height, nCmdShow)){return false;}
    if(!InitDirectX()){return false;}
    if(!InitRtv()){return false;}
    if(!InitCmdAlloc()){return false;}

    return true;
}

void DXWindow::Shutdown(){
    m_swapChain->Release();
}

DXWindow::DXWindow() = default;
DXWindow::~DXWindow() { Shutdown(); }