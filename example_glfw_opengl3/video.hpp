#pragma once
#include <vector>
#include "image.hpp"
class video: public image {
    public:
    int framecount = 0;
    int maxframecount;
    bool videoloaded = false;
    //ID3D11ShaderResourceView* view = NULL; Commented out bc we're using opengl
    std::vector<GLuint> view; //OGL
    video() {

    }
    video(int width, int height, std::string path, std::string name, ImGuiWindowFlags flags) {
        this->width = width;
        this->height = height;
        this->path = path;
        this->name = name;
        this->flags = flags;
    }
    void Begin() {
        if (!videoloaded)
            return;
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(ImVec2(width * this->xstretch + 26, height * this->ystretch + 9));
        float newxpos = this->xpos;
        float leftpivot = 0.0f;
        if (center[0]) {
            setXPosition(io.DisplaySize.x * 0.5f);
            leftpivot = (width * this->xstretch) / (2.0f * ((width * this->xstretch) + 26));
        }
        float newypos = this->ypos;
        float rightpivot = 0.0f;
        if (center[1]) {
            setYPosition(io.DisplaySize.y * 0.5f);
            rightpivot = (height * this->ystretch) / (2.0f * ((height * this->ystretch) + 9));
        }
        ImGui::SetNextWindowPos(ImVec2(newxpos, newypos), ImGuiCond_Always, ImVec2(leftpivot, rightpivot));
        ImGui::Begin(name.c_str(), &enable, flags);
        ImGui::Image((void*)view[framecount], ImVec2(width * this->xstretch, height * this->ystretch), ImVec2(0, 0), ImVec2(1, 1), this->transparency);
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
        framecount++;
        if (framecount > maxframecount)
            framecount = 0;
    }
};
inline video video1 = video(1920, 1080, "C:\\Users\\Exavadeathwitch\\Documents\\GitHub\\NarutoStormImguiTest\\example_glfw_opengl3\\video", "video test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);