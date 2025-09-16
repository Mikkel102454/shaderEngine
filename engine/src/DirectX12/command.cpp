#include "DXWindow.h"

bool DXWindow::InitCmdAlloc() {
    for(UINT i = 0; i < m_bufferCount; i++){
        m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator[i]));
    }
    m_device->CreateCommandList(
            0,
            D3D12_COMMAND_LIST_TYPE_DIRECT,
            m_commandAllocator[0],
            nullptr,
            IID_PPV_ARGS(&m_commandList));
    return true;
}