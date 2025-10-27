// this is heavily inspired by https://github.com/FlR0X/Discord-Overlay-Hijack-External

#include "includes.hpp"
#include "overlay/overlay.hpp"
#include "overlay/menu.hpp"

int main() {
    HWND target = FindWindowA(nullptr, "Discord Overlay");
    if (!target) return 1;

    if (!Overlay::InitD3D(target)) return 1;

    std::thread hookThread(Overlay::StartHooks);

    while (Overlay::running) {
        Overlay::UpdateInput();
        Overlay::RenderFrame([]() {
            if (Menu::open)
                Menu::Draw();
        });
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    hookThread.join();
    Overlay::Shutdown();
}
