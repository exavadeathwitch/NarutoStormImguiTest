#pragma once

#include "messagebox.hpp"
#include "optionlines.hpp"


class optionbox : public messagebox {
public:
	image cursor;
	bool sizecalculated = false;
	bool cursorincrease = true;
	int cursorsetting = 180;
	int cursormin = 180;
	int cursormax = 240;
	std::vector<std::string> textoptions;
	unsigned int optionindex = 0;
	unsigned int optionmax;
	optionbox() {

	}
	optionbox(nineslice* slice, std::string name, std::vector<std::string> textoptions, image cursor) {
		box = slice;
		this->cursor = cursor;
		this->name = name;
		this->textoptions = textoptions;
		this->transparency = 0.0f;
		this->texttransparency = 0.0f;
		for (int x = 0; x < textoptions.size(); x++) {
			text += textoptions.at(x);
			if (x != textoptions.size() - 1)
				text += "\n";
		}
		this->optionmax = textoptions.size() - 1;
		this->cursor.setx1y1({ 0.0f, 0.0f });
		this->cursor.setx2y2({ 1.0f, 1.0f });
	}
	void calculatecursorsize() {
		while (cursor.height != ImGui::GetFontSize()) {
			cursor.setYHeight(ImGui::GetFontSize());
		}
	}
	int Begin() {
		if (!sizecalculated) {
			calculatecursorsize();
			sizecalculated = true;
		}
		if ((timer > -1) && timer == fadeouttime)
			fadeto((2 * FPS / 30), 1);
		switch (choice) {
		case 0:
			break;
		case 1:
			timer = -1;
			if (this->transparency <= 0.0f) {
				this->transparency = 0.0f;
				box->changescale(0.0f);
				choice = 0;
				usetp = false;
				break;
			}
			if (this->transparency == 1.0f)
				box->scale = 1.0f;
			this->transparency -= fadeincrement;
			box->changescale(box->scale - fadeincrement);
			usetp = true;
			break;
		case 2:
			if (this->transparency >= 1.0f) {
				this->transparency = 1.0f;
				box->changescale(1.0f);
				choice = 0;
				usetp = false;
				break;
			}
			if (this->transparency == 0.0f)
				box->changescale(0.0f);
			this->transparency += fadeincrement;
			box->changescale(box->scale + fadeincrement);
			usetp = true;
			break;
		}
		if (this->transparency != 1.0f)
			texttransparency = 0.0f;
		else {
			texttransparency = 1.0f;
		}
		if (usetp) {
			this->centerpointpos = midpoint;
			centerpoint[0] = true;
			centerpoint[1] = true;
		}
		else {
			centerpoint[0] = false;
			centerpoint[1] = false;
			usetp = false;
		}
		if (calculatedmp && transparency == 0.0f) {
			this->width = 0.0f;
			this->height = 0.0f;
			box->changescale(0.0f);
		}
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
		ImGui::SetNextWindowSize({ (float)width, (float)height });
		ImGui::SetNextWindowPos({ newxpos, newypos }, ImGuiCond_None, ImVec2(leftpivot, rightpivot));
		ImGui::Begin(name.c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::End();
		box->transparency.w = transparency;
		box->Begin();
		xpos = box->xpos;
		ypos = box->ypos;
		width = (int)box->width;
		height = (int)box->height;
		if (!calculatedmp) {
			truewidth = width;
			trueheight = height;
			truexpos = xpos;
			trueypos = ypos;
			midpoint = ImVec2(truexpos + (truewidth * 0.5f), trueypos + (trueheight * 0.5f));
			calculatedmp = true;
		}
		if (texttransparency == 0.0f)
			return -2;
		displayText();
		if (timer != -1)
			timer++;
		int retval = -1;
		if (ImGui::IsKeyPressed(ImGuiKey_GamepadFaceDown)) {
			retval = 1;
		}
		if (transparency == 1.0f && choice == 0 && ImGui::IsKeyPressed(ImGuiKey_GamepadFaceRight)) {
			retval = 0;
		}
		return retval;
	}
	void displayText() {
		if (cursorsetting == cursormax)
			cursorincrease = false;
		else if (cursorsetting == cursormin)
			cursorincrease = true;
		if (!cursorincrease)
			cursorsetting--;
		else if (cursorincrease)
			cursorsetting++;
		float cursorfloat = (float)cursorsetting / (float)cursormax;
		if (ImGui::IsKeyPressed(ImGuiKey_GamepadDpadDown) || ImGui::IsKeyPressed(ImGuiKey_GamepadLStickUp))
			if (this->optionindex < this->optionmax)
				this->optionindex++;
		if (ImGui::IsKeyPressed(ImGuiKey_GamepadDpadUp) || ImGui::IsKeyPressed(ImGuiKey_GamepadLStickDown))
			if (this->optionindex > 0)
				this->optionindex--;
		cursor.transparency.w = cursorfloat - 0.3f;
		cursor.setXPosition(xpos);
		cursor.setYPosition(ypos + padding.y + (this->optionindex * ImGui::GetFontSize()));
		cursor.Begin();
		optionlines(name + "_textline", text, width, ImGui::CalcTextSize(text.c_str()).y, xpos, ypos + padding.y, ImVec4(1.0f, 1.0f, 1.0f, (float)texttransparency)).Begin();

	}
};

inline optionbox optiontest = optionbox(&testslice, "optiontest", {"1P Command List", "1P Combo List", "Practice Menu", "Change Jutsu Name Display", "Retry", "Return to Character Select", "Return to Free Battle Menu"}, marker);