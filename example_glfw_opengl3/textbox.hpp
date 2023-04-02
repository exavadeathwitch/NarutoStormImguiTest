#pragma once
#include "nineslice.hpp"
#include "imguiutil.hpp"
#include "textlines.hpp"
#include <imgui_internal.h>
class textbox {
public:
	bool calculated = false;
	bool linecalculated = false;
	bool enable = true;
	bool moveable = true;
	std::string name;
	std::string text;
	nineslice *box;
	ImVec2 padding = {0.0f, 0.0f};
	int xpos;
	int ypos;
	int width;
	int height;
	textlines lines;
	bool center [2] = { false, false };
	bool centerpoint [2] = { false, false };
	ImVec2 centerpointpos;
	float transparency = 1.0f;
	float texttransparency = 1.0f;
	std::string converttexttocenter(std::string str) {
		std::string retval = str;
		while (true) {
			ImVec2 textsize = ImGui::CalcTextSize(retval.c_str());
			if (padding.x + textsize.x > width) {
				break;
			}
			else {
				retval.insert(0, " ");
				retval += " ";
			}
		}
		return retval;
	}
	textbox() {

	}
	textbox(nineslice *slice, std::string name, std::string text) {
		box = slice;
		this->name = name;
		this->text = text;
	}
	void recalculatesize() {
		ImVec2 textsize = ImGui::CalcTextSize(text.c_str());
		while (true) {
			ImVec2 textsizespace = ImGui::CalcTextSize(" ");
			if (textsize.x + 8.0f + (textsizespace.x * 2.0f) > (float)box->width) {
				box->setXStretch(box->xstretch + 0.0001f);
				continue;
			}
			if (textsize.y + 8.0f + (textsizespace.y * 2.0f) > (float)box->height) {
				box->setYStretch(box->ystretch + 0.0001f);
				continue;
			}
			break;
		}
		padding.y = (box->height - textsize.y) / 2.0f;
	}
	void Begin() {
		if (!calculated) {
			recalculatesize();
			calculated = true;
			width = box->width;
			height = box->height;
		}
		//center();
		box->xpos = xpos;
		box->ypos = ypos;
		ImGuiIO& io = ImGui::GetIO();
		float newxpos = this->xpos;
		float leftpivot = 0.0f;
		if (centerpoint[0]) {
			newxpos = centerpointpos.x;
			leftpivot = 0.5f;
			this->box->centerpointpos.x = centerpointpos.x;
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
			this->box->centerpointpos.y = centerpointpos.y;
		}
		else if (center[1]) {
			newypos = io.DisplaySize.y * 0.5f;
			rightpivot = 0.5f;
		}
		for (int x = 0; x < 2; x++) {
			if (center[x])
				box->center[x] = center[x];
			else if (centerpoint[x])
				box->centerpoint[x] = centerpoint[x];
		}
		box->transparency.w = transparency;
		box->Begin();
		xpos = box->xpos;
		ypos = box->ypos;
		width = (int)box->width;
		height = (int)box->height;
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
		ImGui::SetNextWindowSize({ (float)width, (float)height });
		ImGui::SetNextWindowPos({ newxpos, newypos }, ImGuiCond_None, ImVec2(leftpivot, rightpivot));
		ImGui::Begin(name.c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		//ImGui::CenteredText(text.c_str(), ImVec2(box->width + 8.0f, box->height + 8.0f));
		//ImGui::CenteredText("\ntesttest", ImVec2(box->width + 8.0f, box->height + 8.0f + g.Style.WindowPadding.y));
			//ImGui::Text(strings[x].c_str());
		//ImGui::PopStyleVar(1);
		ImGui::End();
		if (texttransparency == 0.0f)
			return;
		textlines(name + "_textline", text, width, height, xpos, ypos + padding.y, ImVec4(1.0f, 1.0f, 1.0f, (float)texttransparency) ).Begin();
	}
};

inline textbox testtext = textbox(&testslice, "asdfasdf", "This game supports autosave. While saving or loading, an icon\nwill be displayed. Do not turn off the power during this time.");