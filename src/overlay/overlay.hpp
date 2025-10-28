#pragma once
#include "../includes.hpp"
#include "menu.hpp"

#pragma comment(lib, "d3d11.lib")
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WTF WHY IS THIS UNDOCUMENTED (https://github.com/ocornut/imgui/blob/master/backends/imgui_impl_win32.cpp#L436)
// if i dont add _Public to name it fails with: multiple definition of `ImGui_ImplWin32_KeyEventToImGuiKey(unsigned long long, long long)';
// wow ig ocornut just doesnt like documenting
ImGuiKey ImGui_ImplWin32_KeyEventToImGuiKey_Public(WPARAM wParam, LPARAM lParam)
{
    if ((wParam == VK_RETURN) && (HIWORD(lParam) & KF_EXTENDED))
        return ImGuiKey_KeypadEnter;

    const int scancode = (int)LOBYTE(HIWORD(lParam));

    switch (wParam)
    {
        case VK_TAB: return ImGuiKey_Tab;
        case VK_LEFT: return ImGuiKey_LeftArrow;
        case VK_RIGHT: return ImGuiKey_RightArrow;
        case VK_UP: return ImGuiKey_UpArrow;
        case VK_DOWN: return ImGuiKey_DownArrow;
        case VK_PRIOR: return ImGuiKey_PageUp;
        case VK_NEXT: return ImGuiKey_PageDown;
        case VK_HOME: return ImGuiKey_Home;
        case VK_END: return ImGuiKey_End;
        case VK_INSERT: return ImGuiKey_Insert;
        case VK_DELETE: return ImGuiKey_Delete;
        case VK_BACK: return ImGuiKey_Backspace;
        case VK_SPACE: return ImGuiKey_Space;
        case VK_RETURN: return ImGuiKey_Enter;
        case VK_ESCAPE: return ImGuiKey_Escape;
        //case VK_OEM_7: return ImGuiKey_Apostrophe;
        case VK_OEM_COMMA: return ImGuiKey_Comma;
        //case VK_OEM_MINUS: return ImGuiKey_Minus;
        case VK_OEM_PERIOD: return ImGuiKey_Period;
        //case VK_OEM_2: return ImGuiKey_Slash;
        //case VK_OEM_1: return ImGuiKey_Semicolon;
        //case VK_OEM_PLUS: return ImGuiKey_Equal;
        //case VK_OEM_4: return ImGuiKey_LeftBracket;
        //case VK_OEM_5: return ImGuiKey_Backslash;
        //case VK_OEM_6: return ImGuiKey_RightBracket;
        //case VK_OEM_3: return ImGuiKey_GraveAccent;
        case VK_CAPITAL: return ImGuiKey_CapsLock;
        case VK_SCROLL: return ImGuiKey_ScrollLock;
        case VK_NUMLOCK: return ImGuiKey_NumLock;
        case VK_SNAPSHOT: return ImGuiKey_PrintScreen;
        case VK_PAUSE: return ImGuiKey_Pause;
        case VK_NUMPAD0: return ImGuiKey_Keypad0;
        case VK_NUMPAD1: return ImGuiKey_Keypad1;
        case VK_NUMPAD2: return ImGuiKey_Keypad2;
        case VK_NUMPAD3: return ImGuiKey_Keypad3;
        case VK_NUMPAD4: return ImGuiKey_Keypad4;
        case VK_NUMPAD5: return ImGuiKey_Keypad5;
        case VK_NUMPAD6: return ImGuiKey_Keypad6;
        case VK_NUMPAD7: return ImGuiKey_Keypad7;
        case VK_NUMPAD8: return ImGuiKey_Keypad8;
        case VK_NUMPAD9: return ImGuiKey_Keypad9;
        case VK_DECIMAL: return ImGuiKey_KeypadDecimal;
        case VK_DIVIDE: return ImGuiKey_KeypadDivide;
        case VK_MULTIPLY: return ImGuiKey_KeypadMultiply;
        case VK_SUBTRACT: return ImGuiKey_KeypadSubtract;
        case VK_ADD: return ImGuiKey_KeypadAdd;
        case VK_LSHIFT: return ImGuiKey_LeftShift;
        case VK_LCONTROL: return ImGuiKey_LeftCtrl;
        case VK_LMENU: return ImGuiKey_LeftAlt;
        case VK_LWIN: return ImGuiKey_LeftSuper;
        case VK_RSHIFT: return ImGuiKey_RightShift;
        case VK_RCONTROL: return ImGuiKey_RightCtrl;
        case VK_RMENU: return ImGuiKey_RightAlt;
        case VK_RWIN: return ImGuiKey_RightSuper;
        case VK_APPS: return ImGuiKey_Menu;
        case '0': return ImGuiKey_0;
        case '1': return ImGuiKey_1;
        case '2': return ImGuiKey_2;
        case '3': return ImGuiKey_3;
        case '4': return ImGuiKey_4;
        case '5': return ImGuiKey_5;
        case '6': return ImGuiKey_6;
        case '7': return ImGuiKey_7;
        case '8': return ImGuiKey_8;
        case '9': return ImGuiKey_9;
        case 'A': return ImGuiKey_A;
        case 'B': return ImGuiKey_B;
        case 'C': return ImGuiKey_C;
        case 'D': return ImGuiKey_D;
        case 'E': return ImGuiKey_E;
        case 'F': return ImGuiKey_F;
        case 'G': return ImGuiKey_G;
        case 'H': return ImGuiKey_H;
        case 'I': return ImGuiKey_I;
        case 'J': return ImGuiKey_J;
        case 'K': return ImGuiKey_K;
        case 'L': return ImGuiKey_L;
        case 'M': return ImGuiKey_M;
        case 'N': return ImGuiKey_N;
        case 'O': return ImGuiKey_O;
        case 'P': return ImGuiKey_P;
        case 'Q': return ImGuiKey_Q;
        case 'R': return ImGuiKey_R;
        case 'S': return ImGuiKey_S;
        case 'T': return ImGuiKey_T;
        case 'U': return ImGuiKey_U;
        case 'V': return ImGuiKey_V;
        case 'W': return ImGuiKey_W;
        case 'X': return ImGuiKey_X;
        case 'Y': return ImGuiKey_Y;
        case 'Z': return ImGuiKey_Z;
        case VK_F1: return ImGuiKey_F1;
        case VK_F2: return ImGuiKey_F2;
        case VK_F3: return ImGuiKey_F3;
        case VK_F4: return ImGuiKey_F4;
        case VK_F5: return ImGuiKey_F5;
        case VK_F6: return ImGuiKey_F6;
        case VK_F7: return ImGuiKey_F7;
        case VK_F8: return ImGuiKey_F8;
        case VK_F9: return ImGuiKey_F9;
        case VK_F10: return ImGuiKey_F10;
        case VK_F11: return ImGuiKey_F11;
        case VK_F12: return ImGuiKey_F12;
        case VK_F13: return ImGuiKey_F13;
        case VK_F14: return ImGuiKey_F14;
        case VK_F15: return ImGuiKey_F15;
        case VK_F16: return ImGuiKey_F16;
        case VK_F17: return ImGuiKey_F17;
        case VK_F18: return ImGuiKey_F18;
        case VK_F19: return ImGuiKey_F19;
        case VK_F20: return ImGuiKey_F20;
        case VK_F21: return ImGuiKey_F21;
        case VK_F22: return ImGuiKey_F22;
        case VK_F23: return ImGuiKey_F23;
        case VK_F24: return ImGuiKey_F24;
        case VK_BROWSER_BACK: return ImGuiKey_AppBack;
        case VK_BROWSER_FORWARD: return ImGuiKey_AppForward;
        default: break;
    }

    switch (scancode)
    {
    case 41: return ImGuiKey_GraveAccent;  // VK_OEM_8 in EN-UK, VK_OEM_3 in EN-US, VK_OEM_7 in FR, VK_OEM_5 in DE, etc.
    case 12: return ImGuiKey_Minus;
    case 13: return ImGuiKey_Equal;
    case 26: return ImGuiKey_LeftBracket;
    case 27: return ImGuiKey_RightBracket;
    case 86: return ImGuiKey_Oem102;
    case 43: return ImGuiKey_Backslash;
    case 39: return ImGuiKey_Semicolon;
    case 40: return ImGuiKey_Apostrophe;
    case 51: return ImGuiKey_Comma;
    case 52: return ImGuiKey_Period;
    case 53: return ImGuiKey_Slash;
    default: break;
    }

    return ImGuiKey_None;
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

        ImGuiKey key = ImGui_ImplWin32_KeyEventToImGuiKey_Public(kb->vkCode, (LPARAM)kb->flags << 16 | kb->scanCode);
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

        LPARAM new_lParam = 1 | (kb->scanCode << 16) | ((kb->flags & LLKHF_EXTENDED) ? (1 << 24) : 0);
        if (ImGui_ImplWin32_WndProcHandler(hwnd, wParam, kb->vkCode, new_lParam))
            return 1;

        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    inline LRESULT CALLBACK MouseLL(int code, WPARAM wParam, LPARAM lParam) {
        if (code != HC_ACTION)
            return CallNextHookEx(nullptr, code, wParam, lParam);

        auto* ms = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
        mousePos = ImVec2(static_cast<float>(ms->pt.x), static_cast<float>(ms->pt.y));
        switch (wParam) {
            case WM_LBUTTONDOWN: leftDown = true; break;
            case WM_LBUTTONUP:   leftDown = false; break;
            case WM_RBUTTONDOWN: rightDown = true; break;
            case WM_RBUTTONUP:   rightDown = false; break;
        }

        LPARAM new_lParam = MAKELPARAM(ms->pt.x, ms->pt.y);
        WPARAM new_wParam = 0;

        if (GetKeyState(VK_CONTROL) & 0x8000) new_wParam |= MK_CONTROL;
        if (GetKeyState(VK_SHIFT) & 0x8000)   new_wParam |= MK_SHIFT;
        if (leftDown)  new_wParam |= MK_LBUTTON;
        if (rightDown) new_wParam |= MK_RBUTTON;

        ImGui_ImplWin32_WndProcHandler(hwnd, wParam, new_wParam, new_lParam);

        if (Menu::open && (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN))
            return 1;

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
            //io.MouseDrawCursor = true;
            if (!cursorHidden) { ShowCursor(FALSE); cursorHidden = true; }
        } else {
            //io.MouseDrawCursor = false;
            if (cursorHidden) { ShowCursor(TRUE); cursorHidden = false; }
        }
    }
}
