#pragma once
#include "../includes.hpp"

namespace Menu {
    inline bool open = true;

    inline void Draw() {
        ImGui::SetWindowSize(ImVec2{500, 500});
        ImGui::Begin("Overlay Hook");
        ImGui::Text("Discord overlay :)");

        // add here

        ImGui::End();
    }
}
