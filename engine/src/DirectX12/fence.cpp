#include "DXWindow.h"

void DXWindow::CreateFenceObjects() {
    m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
    for (UINT i = 0; i < m_bufferCount; ++i) m_fenceValues[i] = 0; // reset fence values

    m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void DXWindow::MoveToNextFrame() {
    const UINT64 fenceToSignal = ++m_fenceValues[m_frameIndex];
    m_commandQueue->Signal(m_fence, fenceToSignal);

    // goto next frame index
    m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

    if(m_fence->GetCompletedValue() < m_fenceValues[m_frameIndex]){
        m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }
}

void DXWindow::WaitForGpu() {
    m_commandQueue->Signal(m_fence, ++m_fenceValues[m_frameIndex]);
    m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_fenceEvent);
    WaitForSingleObject(m_fenceEvent, INFINITE);
}