#pragma once
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>


class DXWindow{
public:
    DXWindow();
    ~DXWindow();

    bool Init(HINSTANCE hInstance, const wchar_t* title, int width, int height, int nCmdShow);
    void Shutdown();

    void Update();
    void Render();

    HWND GetHwnd() const { return m_hwnd; }
private:
    bool InitWindow(HINSTANCE hInstance, const wchar_t* title, int width, int height, int nCmdShow);
    bool InitDirectX();
    bool InitRtv();
    bool InitCmdAlloc();
    bool InitDsv();

    void CreateFenceObjects();
    void MoveToNextFrame();
    void WaitForGpu();

    HWND m_hwnd = nullptr;
    int m_width = 0;
    int m_height = 0;

    static const UINT m_bufferCount = 3;

    IDXGIFactory6* m_factory = nullptr;
    ID3D12Device* m_device = nullptr;
    ID3D12CommandQueue* m_commandQueue = nullptr;
    IDXGISwapChain3* m_swapChain = nullptr;
    ID3D12CommandAllocator* m_commandAllocator[m_bufferCount];
    ID3D12GraphicsCommandList* m_commandList = nullptr;

    ID3D12DescriptorHeap* m_dsvHeap = nullptr;
    UINT m_dsvDescriptorSize = 0;
    ID3D12Resource* m_depthStencil = nullptr;

    ID3D12DescriptorHeap* m_rtvHeap = nullptr;
    UINT m_rtvDescSize = 0;
    ID3D12Resource* m_renderTargets[m_bufferCount];

    ID3D12Fence* m_fence;
    UINT64 m_fenceValues[m_bufferCount];
    HANDLE m_fenceEvent = nullptr;

    UINT m_frameIndex = 0;
};