#pragma once
#include "../includes.hpp"
#include "menu.hpp"

#pragma comment(lib, "d3d11.lib")

ImGuiKey vk_to_imguikey(DWORD vk) {
    if (vk >= 'A' && vk <= 'Z') return static_cast<ImGuiKey>(ImGuiKey_A + (vk - 'A'));

    if (vk >= '0' && vk <= '9') return static_cast<ImGuiKey>(ImGuiKey_0 + (vk - '0'));

    switch (vk) {
        case VK_LEFT:  return ImGuiKey_LeftArrow;
        case VK_RIGHT: return ImGuiKey_RightArrow;
        case VK_UP:    return ImGuiKey_UpArrow;
        case VK_DOWN:  return ImGuiKey_DownArrow;

        case VK_BACK:   return ImGuiKey_Backspace;
        case VK_TAB:    return ImGuiKey_Tab;
        case VK_RETURN: return ImGuiKey_Enter;
        case VK_ESCAPE: return ImGuiKey_Escape;
        case VK_SPACE:  return ImGuiKey_Space;
        case VK_DELETE: return ImGuiKey_Delete;
        case VK_HOME:   return ImGuiKey_Home;
        case VK_END:    return ImGuiKey_End;
        case VK_PRIOR:  return ImGuiKey_PageUp;
        case VK_NEXT:   return ImGuiKey_PageDown;
        case VK_INSERT: return ImGuiKey_Insert;

        case VK_SHIFT:   return ImGuiKey_LeftShift;
        case VK_CONTROL: return ImGuiKey_LeftCtrl;
        case VK_MENU:    return ImGuiKey_LeftAlt;

        case VK_OEM_1:  return ImGuiKey_Semicolon;
        case VK_OEM_PLUS: return ImGuiKey_Equal;
        case VK_OEM_COMMA: return ImGuiKey_Comma;
        case VK_OEM_MINUS: return ImGuiKey_Minus;
        case VK_OEM_PERIOD: return ImGuiKey_Period;
        case VK_OEM_2: return ImGuiKey_Slash;
        case VK_OEM_3: return ImGuiKey_GraveAccent;
        case VK_OEM_4: return ImGuiKey_LeftBracket;
        case VK_OEM_5: return ImGuiKey_Backslash;
        case VK_OEM_6: return ImGuiKey_RightBracket;
        case VK_OEM_7: return ImGuiKey_Apostrophe;

        default: return ImGuiKey_None;
    }
}

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
        if (code != HC_ACTION)
            return CallNextHookEx(nullptr, code, wParam, lParam);

        auto* kb = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        ImGuiIO& io = ImGui::GetIO();
        bool down = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);

        ImGuiKey key = vk_to_imguikey(kb->vkCode);
        if (key != ImGuiKey_None)
            io.AddKeyEvent(key, down);

        io.AddKeyEvent(ImGuiKey_ModCtrl,  (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0);
        io.AddKeyEvent(ImGuiKey_ModShift, (GetAsyncKeyState(VK_SHIFT)   & 0x8000) != 0);
        io.AddKeyEvent(ImGuiKey_ModAlt,   (GetAsyncKeyState(VK_MENU)    & 0x8000) != 0);

        if (down) {
            if (!(GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
                BYTE keyboardState[256] = {};
                GetKeyboardState(keyboardState);

                if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                    keyboardState[VK_SHIFT] |= 0x80;

                WCHAR buffer[5] = {};
                if (ToUnicode(kb->vkCode, kb->scanCode, keyboardState, buffer, 4, 0) > 0) {
                    for (int i = 0; buffer[i]; ++i)
                        io.AddInputCharacter(buffer[i]);
                }
            }
        }

        if (down && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
            switch (kb->vkCode) {
                case 'A': io.AddKeyEvent(ImGuiKey_A, true); break; // Select all
                case 'C': io.AddKeyEvent(ImGuiKey_C, true); break; // Copy
                case 'V': io.AddKeyEvent(ImGuiKey_V, true); break; // Paste
                case 'X': io.AddKeyEvent(ImGuiKey_X, true); break; // Cut
            }
        }

        if (down && kb->vkCode == VK_INSERT)
            Menu::open = !Menu::open;

        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    inline LRESULT CALLBACK MouseLL(int code, WPARAM wParam, LPARAM lParam) {
        if (code == HC_ACTION) {
            auto* ms = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
            mousePos = ImVec2(static_cast<float>(ms->pt.x), static_cast<float>(ms->pt.y));
            switch (wParam) {
                case WM_LBUTTONDOWN: leftDown = true; break;
                case WM_LBUTTONUP:   leftDown = false; break;
                case WM_RBUTTONDOWN: rightDown = true; break;
                case WM_RBUTTONUP:   rightDown = false; break;
            }
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

        static bool cursorHidden = false;
        if (Menu::open) {
            io.MouseDrawCursor = true;
            if (!cursorHidden) { ShowCursor(FALSE); cursorHidden = true; }
        } else {
            io.MouseDrawCursor = false;
            if (cursorHidden) { ShowCursor(TRUE); cursorHidden = false; }
        }
    }
}
