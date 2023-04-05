#pragma once
#include "image.hpp"
#include <vector>
#include <cmath>
class nineslice {
public:
	image slices[9];
    ImVec2 slicedim[9];
    bool moveable = false;
    bool enable = false;
    float defscale = 1.0f;
    float scale = 1.0f;
    float width;
    float height;
    float xpos = 0;
    float ypos = 0;
    bool center[2] = { 0, 0 }; //first value represents if the image is centered on the x-axis, second value represents if the image is centered on the y-axis.
    bool centerpoint[2] = { false, false };
    ImVec2 centerpointpos;
    float xstretch = 1.0f;
    float ystretch = 1.0f;
    ImVec4 transparency = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    float fadeincrement = 0.0f;
    int choice = 0;
    std::string path;
    std::string name;
    //ID3D11ShaderResourceView* view = NULL; Commented out bc we're using opengl
    ImGuiWindowFlags flags;
    nineslice() {

    }
    nineslice(float width, float height, std::vector<ImVec2> coordinates, std::string path, std::string name, ImGuiWindowFlags flags) {
        for (int x = 0; x < 9; x++)
            slices[x] = image((int)coordinates.at(x).x, (int)coordinates.at(x).y, path, name + "_nineslice" + std::to_string(x + 1), flags);
        this->width = width;
        this->height = height;
        this->path = path;
        this->name = name;
        this->flags = flags;
        this->setup();
    }
    void fadeout(int fadeduration) {
        fadeincrement = 1.0f / (float)fadeduration;
        this->choice = 1;
        for (int x = 0; x < 9; x++) {
            slices[x].choice = 1;
            slices[x].fadeincrement = this->fadeincrement;
        }
    }
    void fadein(int fadeduration) {
        fadeincrement = 1.0f / (float)fadeduration;
        this->choice = 2;
        for (int x = 0; x < 9; x++) {
            slices[x].choice = 1;
            slices[x].fadeincrement = this->fadeincrement;
        }
    }
    void setXStretch(float xstretch) {
        this->xstretch = xstretch;
        slices[1].setXStretch(xstretch);
        slices[7].setXStretch(xstretch);
        slicedim[1].x = slices[1].width;
        slicedim[7].x = slices[7].width;
        this->width = slices[0].width + slices[1].width + slices[2].width;
        adjust5xstretch();
    }
    void setYStretch(float ystretch) {
        this->ystretch = ystretch;
        slices[3].setYStretch(ystretch);
        slices[5].setYStretch(ystretch);
        slicedim[3].y = slices[3].height;
        slicedim[5].y = slices[5].height;
        this->height = slices[0].height + slices[3].height + slices[6].height;
        adjust5ystretch();
    }
    void changescale(float num) {
        if (num == 1.0f) {
            this->width = slicedim[0].x + slicedim[1].x + slicedim[2].x;
            this->height = slicedim[0].y + slicedim[3].y + slicedim[6].y;
            for (int x = 0; x < 9; x++) {
                slices[x].width = slicedim[x].x;
                slices[x].height = slicedim[x].y;
            }
            this->scale = num;
            return;
        }
        for (int x = 0; x < 9; x++) {
            slices[x].width = slicedim[x].x * num;
            slices[x].height = slicedim[x].y * num;
        }
        this->width = (slicedim[0].x + slicedim[1].x + slicedim[2].x);
        this->width = this->width * num;
        this->height = (slicedim[0].y + slicedim[3].y + slicedim[6].y);
        this->height = this->height * num;
        this->scale = num;
    }
    void adjust5xstretch() {
        while (slices[3].width + slices[4].width < slices[0].width + slices[1].width + floor(.27f * slices[2].width)) {
            slices[4].setXStretch((float)(slices[4].xstretch + .0001f));
        }
        slicedim[4].x = slices[4].width;
    }
    void adjust5ystretch() {
        while (slices[1].height + (slices[4].height * slices[4].ystretch) < this->height - 8.0f) {
            slices[4].setYStretch((float)(slices[4].ystretch + .0001f));
        }
        slicedim[4].y = slices[4].height;
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
    void setup() {
        slices[0].setx1y1(ImVec2(0, 0));
        slices[0].setx2y2(ImVec2((float)(slices[0].width) / this->width, (float)(slices[0].height) / this->height));
        slices[1].setx1y1(ImVec2(slices[0].x2y2.x, 0));
        slices[1].setx2y2(ImVec2((float)(slices[0].width + slices[1].width) / this->width, slices[0].x2y2.y));
        slices[2].setx1y1(ImVec2(slices[1].x2y2.x, 0));
        slices[2].setx2y2(ImVec2(1.0f, (float)(slices[2].height) / this->height));
        slices[3].setx1y1(ImVec2(0, (float)(slices[0].height) / this->height));
        slices[3].setx2y2(ImVec2((float)(slices[3].width) / this->width, (float)(slices[0].height + slices[3].height) / this->height));
        slices[4].setx1y1(ImVec2(slices[3].x2y2.x, slices[3].x1y1.y));
        slices[4].setx2y2(ImVec2((float)(slices[3].width + slices[4].width) / this->width, (float)(slices[0].height + slices[4].height) / this->height));
        slices[5].setx1y1(ImVec2((float)(this->width - slices[5].width) / this->width, slices[2].x2y2.y));
        slices[5].setx2y2(ImVec2(1.0f, (float)(slices[2].height + slices[5].height) / this->height));
        slices[6].setx1y1(ImVec2(0, (float)(slices[0].height + slices[3].height) / this->height));
        slices[6].setx2y2(ImVec2((float)(slices[6].width) / this->width, 1.0f));
        slices[7].setx1y1(ImVec2(slices[6].x2y2.x, (float)(this->height - slices[7].height) / this->height));
        slices[7].setx2y2(ImVec2((float)(slices[6].width + slices[7].width) / this->width, 1.0f));
        slices[8].setx1y1(ImVec2(slices[7].x2y2.x, slices[7].x1y1.y));
        slices[8].setx2y2(ImVec2(1.0f, 1.0f));
        this->width = slices[0].width + slices[1].width + slices[2].width;
        this->height = slices[0].height + slices[3].height + slices[6].height;
        for (int x = 0; x < 9; x++)
            slicedim[x] = { slices[x].width, slices[x].height };
    }
    void Begin() {
        //this->width = (slicedim[0].x + slicedim[1].x + slicedim[2].x);
        //this->height = (slicedim[0].y + slicedim[3].y + slicedim[6].y);
        ImGuiIO& io = ImGui::GetIO();
        float newxpos = this->xpos;
        float leftpivot = 0.0f;
        if (centerpoint[0]) {
            newxpos = centerpointpos.x;
            leftpivot = 0.5f;
        }
        else if (center[0]) {
            newxpos = io.DisplaySize.x * 0.5f;
            leftpivot = 0.5f;
        }
        float newypos = this->ypos;
        float rightpivot = 0.0f;
        if (centerpoint[1]) {
            newypos = centerpointpos.y;
            rightpivot = 0.5f;
        }
        else if (center[1]) {
            newypos = io.DisplaySize.y * 0.5f;
            rightpivot = 0.5f;
        }
        ImGui::SetNextWindowPos(ImVec2(newxpos, newypos), ImGuiCond_Always, ImVec2(leftpivot, rightpivot));
        ImGui::SetNextWindowSize({ (float)this->width, (float)this->height });
        ImGui::Begin((name + "_whole").c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
        this->xpos = ImGui::GetWindowPos().x;
        this->ypos = ImGui::GetWindowPos().y;
        ImGui::End();

        slices[0].setPosition(this->xpos, this->ypos);
        slices[1].setPosition(slices[0].xpos + slices[0].width + 8, slices[0].ypos + 8);
        slices[2].setPosition(slices[1].xpos + slices[1].width + 8, slices[1].ypos + 8);
        slices[3].setPosition(slices[0].xpos + 8, slices[0].ypos + slices[0].height + 8);
        slices[4].setPosition(slices[3].xpos + slices[3].width + 8, slices[0].ypos + slices[0].height + 8);
        slices[5].setPosition(slices[0].xpos + (slices[0].width + slices[1].width + slices[2].width - slices[5].width) + 8, slices[0].ypos + slices[2].height + 8);
        slices[6].setPosition(slices[0].xpos + 8, slices[3].ypos + slices[3].height + 8);
        slices[7].setPosition(slices[6].xpos + slices[6].width + 8, slices[0].ypos + (slices[0].height + slices[3].height + slices[6].height - slices[7].height) + 8);
        slices[8].setPosition(slices[7].xpos + slices[7].width + 8, slices[5].ypos + slices[5].height + 8);
        if (moveable)
            slices[0].moveable = true;
        else
            slices[0].moveable = false;
        for (int x = 0; x < 9; x++)
            slices[x].transparency = transparency;
        slices[0].Begin();
        if (moveable) {
            slices[1].setPosition(slices[0].xpos + slices[0].width + 8, slices[0].ypos + 8);
            slices[2].setPosition(slices[1].xpos + slices[1].width + 8, slices[1].ypos + 8);
            slices[3].setPosition(slices[0].xpos + 8, slices[0].ypos + slices[0].height + 8);
            slices[4].setPosition(slices[3].xpos + slices[3].width + 8, slices[0].ypos + slices[0].height + 8);
            slices[5].setPosition(slices[0].xpos + (slices[0].width + slices[1].width + slices[2].width - slices[5].width) + 8, slices[0].ypos + slices[2].height + 8);
            slices[6].setPosition(slices[0].xpos + 8, slices[3].ypos + slices[3].height + 8);
            slices[7].setPosition(slices[6].xpos + slices[6].width + 8, slices[0].ypos + (slices[0].height + slices[3].height + slices[6].height - slices[7].height) + 8);
            slices[8].setPosition(slices[7].xpos + slices[7].width + 8, slices[5].ypos + slices[5].height + 8);
        }
        slices[1].Begin();
        slices[2].Begin();
        slices[3].Begin();
        slices[4].Begin();
        slices[5].Begin();
        slices[6].Begin();
        slices[7].Begin();
        slices[8].Begin();
        this->xpos = slices[0].xpos + 8.0f;
        this->ypos = slices[0].ypos + 8.0f;
    }
};
std::vector<ImVec2> coords = { {32, 28}, {20, 28}, {44, 40}, {32, 20}, {32, 32}, {32, 20}, {44, 43}, {20, 31}, {32, 31} };
nineslice testslice = nineslice(96, 91, coords, "slice.png", "nineslicetest", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);

