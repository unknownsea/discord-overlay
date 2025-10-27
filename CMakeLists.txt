cmake_minimum_required(VERSION 3.31)
project(discord_overlay)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(discord_overlay
        src/main.cpp
        src/overlay/overlay.hpp
        src/overlay/menu.hpp
        ext/imgui/imgui.cpp
        ext/imgui/imgui_draw.cpp
        ext/imgui/imgui_tables.cpp
        ext/imgui/imgui_widgets.cpp
        ext/imgui/imgui_impl_win32.cpp
        ext/imgui/imgui_impl_dx11.cpp
)

target_include_directories(discord_overlay PRIVATE
        src
        ext
        ext/ImGui
)

target_link_libraries(discord_overlay
        d3d11
        dxgi
        d3dcompiler
        dwmapi
)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()