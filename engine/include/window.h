#pragma once
#include <windows.h>

// Called when the window is resized
void OnSize(HWND hwnd, UINT flag, int width, int height);

// Main window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Creates and shows a window
HWND WINAPI createWindow(HINSTANCE hInstance, wchar_t* title, int width, int height, int nCmdShow);
