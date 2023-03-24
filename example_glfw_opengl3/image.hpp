#pragma once
#include <string>
#include <imgui.h>
#include <GLFW/glfw3.h>
class image {
public:
    bool enable = false;
    int width;
    int height;
    int xpos = 0;
    int ypos = 0;
    float xstretch = 1.0f;
    float ystretch = 1.0f;
    ImVec4 transparency = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    float fadeincrement = 0.0f;
    int choice = 0;
    std::string path;
    std::string name;
    //ID3D11ShaderResourceView* view = NULL; Commented out bc we're using opengl
    GLuint view; //OGL
    ImGuiWindowFlags flags;
    image(int width, int height, std::string path, std::string name, ImGuiWindowFlags flags) {
        this->width = width;
        this->height = height;
        this->path = path;
        this->name = name;
        this->flags = flags;
        this->view = 0;
    }
    void fadeout(int fadeduration) {
        fadeincrement = 1.0f / (float)fadeduration;
        this->choice = 1;
    }
    void fadein(int fadeduration) {
        fadeincrement = 1.0f / (float)fadeduration;
        this->choice = 2;
    }
    void setXStretch(float xstretch) {
        this->xstretch = xstretch;
    }
    void setYStretch(float ystretch) {
        this->ystretch = ystretch;
    }
    void setPosition(int xpos, int ypos) {
        this->xpos = xpos - 10;
        this->ypos = ypos - 10;
    }
    void Begin() {
        ImGui::SetNextWindowSize(ImVec2(width * this->xstretch + 50, height * this->ystretch + 10));
        //ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin(name.c_str(), &enable, flags);
        ImGui::Image((void*)view, ImVec2(width * this->xstretch, height * this->ystretch), ImVec2(0, 0), ImVec2(1, 1), this->transparency);
        switch (this->choice) {
        case 0:
            break;
        case 1:
            this->transparency.w -= this->fadeincrement;
            if (transparency.w < 0.0f) {
                transparency.w = 0.0f;
                choice = 0;
            }
            break;
        case 2:
            this->transparency.w += this->fadeincrement;
            if (transparency.w > 1.0f) {
                transparency.w = 1.0f;
                choice = 0;
            }
            break;
        }
        ImGui::End();
    }
};
image image1 = image(1280, 720, "test.png", "image test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
