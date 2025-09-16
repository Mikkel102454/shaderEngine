#include "DXWindow.h"

#include <iostream>

void GetAdapter(IDXGIFactory6* factory, IDXGIAdapter1** adapter);
HRESULT CreateDevice(IDXGIAdapter1* adapter, ID3D12Device** device, D3D_FEATURE_LEVEL level);
HRESULT CreateCommandQueue(ID3D12Device* device,
                           const D3D12_COMMAND_QUEUE_DESC& desc,
                           ID3D12CommandQueue** queue);
HRESULT CreateSwapChain(IDXGIFactory6* factory, ID3D12CommandQueue* queue, HWND hwnd,
                        const DXGI_SWAP_CHAIN_DESC1& scDesc,
                        const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fScDesc,
                        IDXGIOutput* output, IDXGISwapChain1** swapChain);



bool DXWindow::InitDirectX() {
    UINT factoryFlags = 0;
    IDXGIFactory6* factory;

    if(FAILED(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&factory)))) std::cout << "HRESULT of CreateDXGIFactory2 is not S_OK\n";

    IDXGIAdapter1* adapter = nullptr;
    GetAdapter(factory, &adapter);

    if (FAILED(CreateDevice(adapter, &m_device, D3D_FEATURE_LEVEL_11_0)))
        std::cout << "CreateDevice failed\n";

    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;

    if (FAILED(CreateCommandQueue(m_device, desc, &m_commandQueue)))
        std::cout << "CreateCommandQueue failed\n";

    DXGI_SWAP_CHAIN_DESC1 scDesc{};
    scDesc.Width       = 0;                         // use window client size
    scDesc.Height      = 0;
    scDesc.Format      = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.SampleDesc  = { 1, 0 };                  // REQUIRED for flip-model
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.BufferCount = m_bufferCount;
    scDesc.SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scDesc.Flags       = 0;                         // add ALLOW_TEARING later if desired

    IDXGISwapChain1* swapChain = nullptr;
    HRESULT hr = CreateSwapChain(factory, m_commandQueue, m_hwnd, scDesc, nullptr, nullptr, &swapChain);

    if (FAILED(hr)) {
        std::cout << "CreateSwapChain failed, hr=0x" << std::hex << (unsigned)hr << std::dec << "\n";
        return -1;
    }
    std::cout << "CreateSwapChain created\n";

    hr = swapChain->QueryInterface(IID_PPV_ARGS(&m_swapChain));
    swapChain->Release();

    return SUCCEEDED(hr);
}


void GetAdapter(IDXGIFactory6* factory, IDXGIAdapter1** adapter) {
    for (UINT i = 0; factory->EnumAdapters1(i, adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC1 desc;
        (*adapter)->GetDesc1(&desc);
    }
}

HRESULT CreateDevice(IDXGIAdapter1* adapter, ID3D12Device** device, D3D_FEATURE_LEVEL level) {
    return D3D12CreateDevice(adapter, level, IID_PPV_ARGS(device));
}

HRESULT CreateCommandQueue(ID3D12Device* device,
                           const D3D12_COMMAND_QUEUE_DESC& desc,
                           ID3D12CommandQueue** queue) {
    return device->CreateCommandQueue(&desc, IID_PPV_ARGS(queue));
}

HRESULT CreateSwapChain(IDXGIFactory6* factory, ID3D12CommandQueue* queue, HWND hwnd,
                        const DXGI_SWAP_CHAIN_DESC1& scDesc,
                        const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fScDesc,
                        IDXGIOutput* output, IDXGISwapChain1** swapChain) {
    return factory->CreateSwapChainForHwnd(queue, hwnd, &scDesc, fScDesc, output, swapChain);
}
