#include "appLoop.h"
#include "DXWindow.h"
bool PumpMessages(){
    MSG msg;
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
        if(msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void DXWindow::Update() {

}