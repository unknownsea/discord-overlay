#pragma once
#include "../includes.hpp"
#include "../../ext/imgui_texteditor/TextEditor.h"


namespace Menu {
    inline bool open = true;

    inline void Draw() {
        if (!open) return;

        static TextEditor editor;
        editor.SetLanguageDefinition(TextEditor::LanguageDefinitionId::Lua);
        static bool initialized = false;

        if (!initialized) {
            initialized = true;
            editor.SetText("print('print') -- comment");
            editor.SetPalette(TextEditor::PaletteId::Dark);
        }

        ImGui::SetNextWindowSize(ImVec2{700, 600}, ImGuiCond_FirstUseEver);
        ImGui::Begin("overlay hook", nullptr, ImGuiWindowFlags_NoCollapse);

        editor.Render("TextEditor");

        ImGui::End();
    }
}
