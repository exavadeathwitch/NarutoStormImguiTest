#pragma once
#include <string>
#include <imgui.h>
#include <GLFW/glfw3.h>
class image {
public:
    bool moveable = false;
    bool enable = true;
    float width;
    float height;
    int widthint;
    int heightint;
    float xpos = 0;
    float ypos = 0;
    bool center[2] = {0, 0}; //first value represents if the image is centered on the x-axis, second value represents if the image is centered on the y-axis.
    float xstretch = 1.0f;
    float ystretch = 1.0f;
    ImVec2 x1y1;
    ImVec2 x2y2;
    ImVec4 transparency = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    float fadeincrement = 0.0f;
    int choice = 0;
    std::string path;
    std::string name;
    //ID3D11ShaderResourceView* view = NULL; Commented out bc we're using opengl
    GLuint view; //OGL
    ImGuiWindowFlags flags;
    image() {

    }
    image(int width, int height, std::string path, std::string name, ImGuiWindowFlags flags) {
        this->width = width;
        this->widthint = width;
        this->height = height;
        this->heightint = height;
        this->path = path;
        this->name = name;
        this->flags = flags;
        this->view = 0;
    }
    void setx1y1(ImVec2 x1y1) {
        this->x1y1 = x1y1;
    }
    void setx2y2(ImVec2 x2y2) {
        this->x2y2 = x2y2;
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
        this->width = this->width * xstretch;
    }
    void setYStretch(float ystretch) {
        this->ystretch = ystretch;
        this->height = this->height * ystretch;
    }
    void setYHeight(float yheight) {
        this->ystretch = yheight / this->height;
        this->height = yheight;
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
        if (!enable)
            return;
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(ImVec2(width + 26, height + 9));
        float newxpos = this->xpos;
        float leftpivot = 0.0f;
        if (center[0]) {
            setXPosition(io.DisplaySize.x * 0.5f);
            leftpivot = (width) / (2.0f * ((width) + 26));
        }
        float newypos = this->ypos;
        float rightpivot = 0.0f;
        if (center[1]) {
            setYPosition(io.DisplaySize.y * 0.5f);
            rightpivot = (height) / (2.0f * ((height) + 9));
        }
        bool movement = false;
        if (!moveable) {
            ImGui::SetNextWindowPos(ImVec2(newxpos, newypos), ImGuiCond_Always, ImVec2(leftpivot, rightpivot));
        }
        else
            movement = true;
        ImGui::Begin(name.c_str(), &enable, flags);
        ImGui::Image((void*)view, ImVec2(width, height), x1y1, x2y2, this->transparency);
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
        if (movement) {
            this->xpos = ImGui::GetWindowPos().x;
            this->ypos = ImGui::GetWindowPos().y;
        }
        ImGui::End();
    }
};
inline image image1 = image(1280, 720, "test.png", "image test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image image2 = image(960, 540, "test2.png", "imagef test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image image3 = image(1920, 1080, "test3.png", "imageff test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest1 = image(32, 28, "slice.png", "imageff test1", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest2 = image(20, 28, "slice.png", "imageff test2", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest3 = image(44, 40, "slice.png", "imageff test3", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest4 = image(32, 20, "slice.png", "imageff test4", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest5 = image(32, 32, "slice.png", "imageff test5", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest6 = image(32, 20, "slice.png", "imageff test6", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest7 = image(44, 43, "slice.png", "imageff test7", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest8 = image(20, 31, "slice.png", "imageff test8", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image imagetest9 = image(32, 31, "slice.png", "imageff test9", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
inline image marker = image(440, 36, "marker.png", "marker test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
//inline image imagetest = image(960, 540, "test3.png", "imageff test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);