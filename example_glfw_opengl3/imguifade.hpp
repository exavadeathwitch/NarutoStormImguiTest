#pragma once

#include <imgui.h>
#include <string>
class imguifade {
public:
    std::string name1;
    std::string name2;
    bool test = true;
    bool fading = false;
    float fadeincrement = 0;
    int choice = 0; //1 for nothing to black, 2 for nothing to white, 3 for black to white, 4 for white to black, 5 for black to nothing, 6 for white to nothing
    ImVec4 blackcolor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 whitecolor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    imguifade(std::string name1, std::string name2) {
        this->name1 = name1;
        this->name2 = name2;
    };
    void imguifadeto(int fadeduration, int choice) {
        fadeincrement = 1.0f / (float)fadeduration;
        this->choice = choice;
    }
    void imguifadeloop() {
        switch (this->choice) {
            case 0:
                blackcolor.w = 0.0f;
                whitecolor.w = 0.0f;
                break;
            case 1: {
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                ImVec4 prevcolor2 = prevstyle.Colors[ImGuiCol_FrameBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->blackcolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                blackcolor.w += this->fadeincrement;
                if (blackcolor.w > 1.0f)
                    blackcolor.w = 1.0f;
                break;
            }
            case 2: {
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                ImVec4 prevcolor2 = prevstyle.Colors[ImGuiCol_FrameBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->whitecolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                whitecolor.w += this->fadeincrement;
                if (whitecolor.w > 1.0f)
                    whitecolor.w = 1.0f;
                break;
            }
            case 3: {
                blackcolor.w = 1.0f;
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->blackcolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                prevstyle.Colors[ImGuiCol_WindowBg] = this->whitecolor;
                ImGui::Begin(this->name2.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                whitecolor.w += this->fadeincrement;
                if (whitecolor.w > 1.0f) {
                    whitecolor.w = 1.0f;
                    blackcolor.w = 0.0f;
                }
                break;
            }
            case 4: {
                whitecolor.w = 1.0f;
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->whitecolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                prevstyle.Colors[ImGuiCol_WindowBg] = this->blackcolor;
                ImGui::Begin(this->name2.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                blackcolor.w += this->fadeincrement;
                if (blackcolor.w > 1.0f) {
                    blackcolor.w = 1.0f;
                    whitecolor.w = 0.0f;
                }
                break;
            }
            case 5: {
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                ImVec4 prevcolor2 = prevstyle.Colors[ImGuiCol_FrameBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->blackcolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                blackcolor.w -= this->fadeincrement;
                if (blackcolor.w < 0.0f)
                    blackcolor.w = 0.0f;
                break;
            }
            case 6: {
                bool use_work_area = true;
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
                ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
                ImGuiStyle& prevstyle = ImGui::GetStyle();
                ImVec4 prevcolor = prevstyle.Colors[ImGuiCol_WindowBg];
                ImVec4 prevcolor2 = prevstyle.Colors[ImGuiCol_FrameBg];
                prevstyle.Colors[ImGuiCol_WindowBg] = this->whitecolor;
                ImGui::Begin(this->name1.c_str(), &test, flags);
                ImGui::End();
                prevstyle.Colors[ImGuiCol_WindowBg] = prevcolor;
                whitecolor.w -= this->fadeincrement;
                if (whitecolor.w < 0.0f)
                    whitecolor.w = 0.0f;
                break;
            }
        }
    }
};

inline imguifade fade = imguifade("asdf", "asdf2");
