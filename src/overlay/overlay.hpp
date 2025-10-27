#pragma once
#include "../includes.hpp"
#include "menu.hpp"

#pragma comment(lib, "d3d11.lib")

namespace Overlay {

    inline HWND hwnd = nullptr;
    inline IDXGISwapChain* swapChain = nullptr;
    inline ID3D11Device* device = nullptr;
    inline ID3D11DeviceContext* context = nullptr;
    inline ID3D11RenderTargetView* rtv = nullptr;

    inline std::atomic<int> width{0};
    inline std::atomic<int> height{0};
    inline std::atomic<bool> running{true};

    inline ImVec2 mousePos{};
    inline bool leftDown = false;
    inline bool rightDown = false;
    inline HHOOK kbHook = nullptr;
    inline HHOOK mouseHook = nullptr;

    inline LRESULT CALLBACK KeyboardLL(int code, WPARAM wParam, LPARAM lParam) {
        if (code == HC_ACTION && wParam == WM_KEYDOWN) {
            auto* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
            if (kb->vkCode == VK_INSERT)
                Menu::open = !Menu::open;
            else if (kb->vkCode == VK_DELETE)
                running = false;
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    inline LRESULT CALLBACK MouseLL(int code, WPARAM wParam, LPARAM lParam) {
        if (code == HC_ACTION) {
            auto* ms = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
            mousePos = ImVec2(static_cast<float>(ms->pt.x), static_cast<float>(ms->pt.y));
            leftDown  = (wParam == WM_LBUTTONDOWN)  ? true  : (wParam == WM_LBUTTONUP)  ? false : leftDown;
            rightDown = (wParam == WM_RBUTTONDOWN) ? true  : (wParam == WM_RBUTTONUP) ? false : rightDown;
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    inline void StartHooks() {
        kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardLL, nullptr, 0);
        mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseLL, nullptr, 0);

        MSG msg{};
        while (running) {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        if (kbHook) UnhookWindowsHookEx(kbHook);
        if (mouseHook) UnhookWindowsHookEx(mouseHook);
    }

    inline bool InitD3D(HWND target) {
        hwnd = target;

        DXGI_SWAP_CHAIN_DESC sd{};
        sd.BufferCount = 2;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL featureLevel;
        D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
        if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                                 levels, 2, D3D11_SDK_VERSION,
                                                 &sd, &swapChain, &device, &featureLevel, &context)))
            return false;

        ID3D11Texture2D* backBuffer = nullptr;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
        backBuffer->Release();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(device, context);

        RECT r;
        GetClientRect(hwnd, &r);
        width = r.right - r.left;
        height = r.bottom - r.top;

        return true;
    }

    inline void RenderFrame(std::function<void()> drawFunc) {
        RECT r;
        if (GetClientRect(hwnd, &r)) {
            int w = r.right - r.left;
            int h = r.bottom - r.top;
            if (w != width || h != height) {
                width = w; height = h;
                if (swapChain) {
                    ImGui_ImplDX11_InvalidateDeviceObjects();
                    if (rtv) { rtv->Release(); rtv = nullptr; }
                    swapChain->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0);
                    ID3D11Texture2D* backBuffer = nullptr;
                    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
                    device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
                    backBuffer->Release();
                    ImGui_ImplDX11_CreateDeviceObjects();
                }
            }
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        drawFunc();

        ImGui::EndFrame();
        ImGui::Render();
        const float clear[4] = {0,0,0,0};
        context->OMSetRenderTargets(1, &rtv, nullptr);
        context->ClearRenderTargetView(rtv, clear);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swapChain->Present(1,0);
    }

    inline void Shutdown() {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        if (rtv) { rtv->Release(); rtv = nullptr; }
        if (swapChain) { swapChain->Release(); swapChain = nullptr; }
        if (context) { context->Release(); context = nullptr; }
        if (device) { device->Release(); device = nullptr; }
    }

    inline void UpdateInput() {
        ImGuiIO& io = ImGui::GetIO();
        POINT p = { static_cast<LONG>(mousePos.x), static_cast<LONG>(mousePos.y) };
        ScreenToClient(hwnd, &p);
        io.MousePos = ImVec2(static_cast<float>(p.x), static_cast<float>(p.y));
        io.MouseDown[0] = leftDown;
        io.MouseDown[1] = rightDown;
        io.MouseDrawCursor = true;
    }
}
