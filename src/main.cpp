#include "iostream"
#include "includes.hpp"
#include "overlay/overlay.hpp"
#include "overlay/menu.hpp"

int main() {
    HWND target = FindWindowA("Chrome_WidgetWin_1", "Discord Overlay");
    if (!target) {
        std::cout << "[-] Overlay not found, exiting" << std::endl;
        return 1;
    }
    std::cout << "[+] Overlay found" << std::endl;

    if (!Overlay::InitD3D(target)) {
        std::cout << "[-] D3D failed initialization, exiting" << std::endl;
        return 1;
    }
    std::cout << "[+] D3D Initialized" << std::endl;

    std::thread hookThread(Overlay::StartHooks);
    if (!hookThread.joinable()) {
        std::cout << "[-] Failed to start hook thread, exiting" << std::endl;
        return 1;
    }
    std::cout << "[+] Hook thread started" << std::endl;

    while (Overlay::running) {
        if (!IsWindow(target)) {
            std::cout << "[-] Overlay window closed or lost, exiting" << std::endl;
            Overlay::running = false;
            break;
        }

        Overlay::UpdateInput();
        Overlay::RenderFrame([]() {
            if (Menu::open)
                Menu::Draw();
        });
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    hookThread.join();
    std::cout << "[?] Threads combined" << std::endl;

    Overlay::Shutdown();
    std::cout << "[?] Overlay shutdown" << std::endl;

    return 0;
}
