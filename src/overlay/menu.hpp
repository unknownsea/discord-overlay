#pragma once
#include "../includes.hpp"
#include "../../ext/imgui_texteditor/TextEditor.h"

namespace Menu {
    inline bool open = true;

    inline void Style() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg]      = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_TitleBg]       = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_Button]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        colors[ImGuiCol_ButtonActive]  = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_Header]        = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_HeaderActive]  = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        colors[ImGuiCol_Border]        = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    }

    inline void Draw() {
        if (!open) return;

        static TextEditor editor;
        editor.SetLanguageDefinition(TextEditor::LanguageDefinitionId::Lua);
        static bool initialized = false;

        if (!initialized) {
            initialized = true;
            Style();
            editor.SetText(R"(getmetatable("").__call = function( self, ... )
    print(self)
end

("Hello World")(print))");
            editor.SetPalette(TextEditor::PaletteId::Neutral);
        }

        ImGui::SetNextWindowSize(ImVec2{500, 500}, ImGuiCond_FirstUseEver);
        ImGui::Begin("overlay hook", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        editor.Render("TextEditor");

        ImGui::End();
    }
}
