#include "DXWindow.h"
#include "external/d3dx12.h"
#include "iostream"

void DXWindow::Render() {
    const float clearColor[4] = {
            255,
            255,
            255,
            255,
    };

    ID3D12CommandAllocator * alloc = m_commandAllocator[m_frameIndex];

    // Wait for gpu to finish
    if(m_fence->GetCompletedValue() < m_fenceValues[m_frameIndex]){
        m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }

    // Reset shit
    alloc->Reset();
    m_commandList->Reset(alloc, nullptr); // PSO as nullptr

    //PRESENT -> RENDER_TARGET for current back buffer
    {
        ID3D12Resource* resource = m_renderTargets[m_frameIndex];
        CD3DX12_RESOURCE_BARRIER b = CD3DX12_RESOURCE_BARRIER::Transition(
                resource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        m_commandList->ResourceBarrier(1, &b);
    }

    // rtv and dsv handles for frame
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtv(
            m_rtvHeap->GetCPUDescriptorHandleForHeapStart(),
            static_cast<INT>(m_frameIndex),
            m_rtvDescSize
            );
    D3D12_CPU_DESCRIPTOR_HANDLE dsv = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();

    m_commandList->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
    m_commandList->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
    m_commandList->ClearDepthStencilView(dsv, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


    // TODO: set viewport/scissor, root sig, descriptor heaps (CBV/SRV/UAV), PSO,
    //       vertex/index buffers, topology, constants, then DrawIndexed(6)

    // Transition back RENDER_TARGET -> PRESENT
    {
        ID3D12Resource* resource = m_renderTargets[m_frameIndex];
        CD3DX12_RESOURCE_BARRIER b = CD3DX12_RESOURCE_BARRIER::Transition(
                resource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        m_commandList->ResourceBarrier(1, &b);
    }

    m_commandList->Close();
    ID3D12CommandList* lists[] = { m_commandList };

    m_swapChain->Present(1, 0); // vsync

    MoveToNextFrame();
}