#pragma once
#include <Windows.h>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>
#include <cassert>
#include <cstdint>
#include <d3d11.h>
#include <tchar.h>

#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_impl_win32.h"