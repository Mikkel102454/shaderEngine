cmake_minimum_required(VERSION 3.29)

# Build the engine code as a static library
add_library(engine STATIC
        src/window.cpp
        src/appLoop.cpp
        src/DirectX12/dxgiFactory.cpp
        src/DirectX12/rtv.cpp
        src/DirectX12/command.cpp
        src/DirectX12/fence.cpp
        src/Pipeline/renderer.cpp
        src/DXWindow.cpp

        include/window.h
        include/appLoop.h
        include/DXWindow.h

        #d3dx12
        include/external/d3dx12.h
)

# Public headers are in engine/include
target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable C++20 and Unicode for WinAPI
target_compile_features(engine PUBLIC cxx_std_20)
target_compile_definitions(engine PUBLIC UNICODE _UNICODE)

# Platform-specific defines and libraries
if (WIN32)
    target_compile_definitions(engine PUBLIC PLATFORM_WINDOWS)
    target_link_libraries(engine PUBLIC dxgi d3d12 user32 gdi32)
elseif(APPLE)
    target_compile_definitions(engine PUBLIC PLATFORM_MACOS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(engine PUBLIC PLATFORM_LINUX)
endif()
