#pragma once

#include <string>
#include <vector>
#include <imgui.h>

class line {
public:
	float xpadding;
	std::string text;
	float xsize;
	float ysize;
	line(float xpadding, std::string text, float xsize, float ysize) {
		this->xpadding = xpadding;
		this->text = text;
		this->xsize = xsize;
		this->ysize = ysize;
	}
};

class textlines {
public:
	std::vector<line> lines;
	std::string name;
	bool enable = true;
	float width;
	float height;
	float xpos;
	float ypos;
	ImVec4 transparency = { 1.0f, 1.0f, 1.0f, 1.0f };
	std::vector<line> splitStringIntoLines(const std::string& str)
	{
		std::vector<line> tokens;

		std::stringstream ss(str);
		std::string token;
		while (std::getline(ss, token, '\n')) {
			ImVec2 textsize = ImGui::CalcTextSize(token.c_str());
			float padding = (this->width - textsize.x) / 2.0f;
			tokens.push_back(line(padding, token, textsize.x + (padding * 2), textsize.y));
		}

		return tokens;
	}
	textlines() {

	}
	textlines(std::string name, std::string text, float width, float height, float xpos, float ypos, ImVec4 transparency = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)) {
		this->name = name;
		this->width = width;
		this->height = height;
		this->xpos = xpos;
		this->ypos = ypos;
		this->transparency = transparency;
		lines = splitStringIntoLines(text);
	}
	void Begin() {
		if (!enable)
			return;
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 og = style->Colors[ImGuiCol_Text];
		style->Colors[ImGuiCol_Text].w = this->transparency.w;
		ImGui::SetNextWindowSize({ (float)this->width, (float)this->height });
		ImGui::SetNextWindowPos({ (float)this->xpos, (float)this->ypos });
		ImGui::Begin(name.c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::End();
		for (int x = 0; x < lines.size(); x++) {
			ImGui::SetNextWindowSize({ lines.at(x).xsize, lines.at(x).ysize });
			ImGui::SetNextWindowPos({ (float)this->xpos, (x * lines.at(x).ysize) + (float)this->ypos });
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { lines.at(x).xpadding, 0 });
			ImGui::Begin((name + std::to_string(x) + lines.at(x).text).c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
			ImGui::Text(lines.at(x).text.c_str());
			ImGui::End();
			ImGui::PopStyleVar(1);
		}
		style->Colors[ImGuiCol_Text].w = og.w;
	}
};