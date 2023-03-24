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
        float xstretch = 2.0f;
        float ystretch = 1.0f;
        float transparency = 1.0f;
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
            ImGui::SetNextWindowSize(ImVec2(width * this->xstretch, height * this->ystretch));
            ImGui::Begin(name.c_str(), &enable, flags);
        }
        void displayImage() {
            ImGui::Image((void*)view, ImVec2(width * this->xstretch, height * this->ystretch));
        }
        void End() {
            ImGui::End();
        }
};
image image1 = image(1280, 720, "test.png", "image test", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
