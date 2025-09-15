cmake_minimum_required(VERSION 3.29)
project(shaderEngine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(engine)

add_executable(shaderEngine
        engine/src/main.cpp
)

target_compile_definitions(shaderEngine PRIVATE UNICODE _UNICODE)
target_link_libraries(shaderEngine PRIVATE engine)