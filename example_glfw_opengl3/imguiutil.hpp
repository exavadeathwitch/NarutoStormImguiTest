#pragma once
#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
    void CenteredText(const char* label, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImVec2 pos2 = ImVec2((pos.x + size.x), (pos.y + size.y));
        const ImRect bb(pos, pos2);

        ItemSize(size, style.FramePadding.y);

        const ImVec2 pos_min = ImVec2((bb.Min.x + style.FramePadding.x), (bb.Min.y + style.FramePadding.y));
        const ImVec2 pos_max = ImVec2((bb.Max.x - style.FramePadding.x), (bb.Max.y - style.FramePadding.y));

        RenderTextClipped(pos_min, pos_max, label, NULL, &label_size, style.ButtonTextAlign, &bb);
    }
}