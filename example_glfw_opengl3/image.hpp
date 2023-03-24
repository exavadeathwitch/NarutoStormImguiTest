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
    bool center[2] = {0, 0}; //first value represents if the image is centered on the x-axis, second value represents if the image is centered on the y-axis.
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
        this->xpos = xpos - 8;
        this->ypos = ypos - 8;
    }
    void setXPosition(int xpos) {
        this->xpos = xpos - 8;
    }
    void setYPosition(int ypos) {
        this->ypos = ypos - 8;
    }
    void Begin() {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(ImVec2(width * this->xstretch + 26, height * this->ystretch + 9));
        float newxpos = this->xpos;
        float leftpivot = 0.0f;
        if (center[0]) {
            setXPosition(io.DisplaySize.x * 0.5f);
            leftpivot = width / (2.0f * (width + 26));
        }
        float newypos = this->ypos;
        float rightpivot = 0.0f;
        if (center[1]) {
            setYPosition(io.DisplaySize.y * 0.5f);
            rightpivot = height / (2.0f * (height + 9));
        }
        ImGui::SetNextWindowPos(ImVec2(newxpos, newypos), ImGuiCond_Always, ImVec2(leftpivot, rightpivot));
        ImGui::Begin(name.c_str(), &enable, flags);
        //ImGui::Text(std::to_string(ImGui::GetWindowPos().x).c_str());
        //ImGui::Text(std::to_string(ImGui::GetWindowPos().y).c_str());
        //ImGui::Text(std::to_string(ImGui::GetWindowSize().x).c_str());
        //ImGui::Text(std::to_string(ImGui::GetWindowSize().y).c_str());
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
