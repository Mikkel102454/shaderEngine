#pragma once
#include <windows.h>
#include <dxgi1_6.h>
#include <iostream>
#include <D3d12.h>

int SetupDxgiFactory(HWND hwnd, IDXGISwapChain3** outSwapChain);
