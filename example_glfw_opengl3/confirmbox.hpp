#pragma once

#include "messagebox.hpp"
#include "sound.hpp"
class confirmbox : public messagebox {
public:
	bool returnonback = false;
	confirmbox() {

	}
	confirmbox(nineslice* slice, std::string name, std::string text) {
		box = slice;
		this->name = name;
		this->text = text;
		this->transparency = 0.0f;
		this->texttransparency = 0.0f;
	}
	void Begin() {
		if (ImGui::IsKeyPressed(ImGuiKey_GamepadFaceDown)) {
			fadeto((2 * FPS / 30), 1);
		}
		if (returnonback && transparency == 1.0f && choice == 0 && ImGui::IsKeyPressed(ImGuiKey_GamepadFaceRight)) {
			fadeto((2 * FPS / 30), 1);
		}
		messagebox::Begin();
	}
};

inline confirmbox confirmtest = confirmbox(&testslice, "confirmtexttest", "I hope you all are doing well,\nbut I'm not done with modding yet.");