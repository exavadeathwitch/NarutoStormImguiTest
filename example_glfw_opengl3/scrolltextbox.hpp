#pragma once

#include "messagebox.hpp"
#include <cmath>
class scrolltextbox : public messagebox {
public:
	float tempheight = 0;
	int textboxheight = 0;
	int textboxwidth = 0;
	int confirmchoice = 2; //If set to 1, can accept at any time. If set to 2, can accept only on max scroll.
	int rejectchoice = 1; //If set to 1, can reject at any time.
	bool confirmonscrolldown = false;
	std::vector<std::string> texts;
	void splitstrings() {
		std::string newstr = text;
		while (newstr.length() > 0) {
			if (newstr.length() > 3000) {
				texts.push_back(newstr.substr(0, 3000));
				newstr = newstr.substr(3000);
			}
			else {
				texts.push_back(newstr);
				newstr = newstr.substr(newstr.length());
			}

		}
	}
	scrolltextbox() {

	}
	scrolltextbox(nineslice* slice, std::string name, std::string text, int textboxwidth, int textboxheight) {
		box = slice;
		this->name = name;
		this->text = text;
		this->textboxwidth = textboxwidth;
		this->textboxheight = textboxheight;
		this->transparency = 0.0f;
		this->texttransparency = 0.0f;
	}
	void recalculatesize() {
		std::string textwidth = "";
		for (int x = 0; x < textboxwidth; x++)
			textwidth += " ";
		for (int x = 0; x < textboxheight; x++)
			textwidth += "\n";
		ImVec2 textsize = ImGui::CalcTextSize(textwidth.c_str());
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
		std::string newtext = "";
		tempheight = ImGui::CalcTextSize(textwidth.c_str()).y;
		padding.y = (box->height - textsize.y) / 2.0f;
	}
	void Begin() {
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
			splitstrings();
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
		ImGui::SetNextWindowSize({ (float)width, (float)height });
		ImGui::SetNextWindowPos({ newxpos, newypos }, ImGuiCond_None, ImVec2(leftpivot, rightpivot));
		ImGui::Begin(name.c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::End();
		if (!calculatedmp) {
			truewidth = width;
			trueheight = height;
			truexpos = xpos;
			trueypos = ypos;
			midpoint = ImVec2(truexpos + (truewidth * 0.5f), trueypos + (trueheight * 0.5f));
			calculatedmp = true;
		}
		if (texttransparency == 0.0f)
			return;
		displayText();
		if (timer != -1)
			timer++;
	}
	void displayText() {
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 og = style->Colors[ImGuiCol_Text];
		style->Colors[ImGuiCol_Text].w = transparency;
		int tempxpos;
		float tempypos = ypos + padding.y;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { ImGui::GetFontSize(), 0});
		ImGui::SetNextWindowSize({ (float)this->width, tempheight });
		ImGui::SetNextWindowPos({ (float)this->xpos, (float)tempypos });
		ImGui::Begin((name + "_wrapped").c_str(), &enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		for (int x = 0; x < texts.size(); x++)
			ImGui::TextWrapped(texts[x].c_str());
		if (transparency == 1.0f && choice == 0) {
			if (confirmchoice == 1 && ImGui::IsKeyPressed(ImGuiKey_GamepadFaceDown))
				fadeto((2 * FPS / 30), 1);
			if (confirmchoice == 2 && ImGui::GetScrollMaxY() == ImGui::GetScrollY() && ImGui::IsKeyPressed(ImGuiKey_GamepadFaceDown))
				fadeto((2 * FPS / 30), 1);
			if (rejectchoice == 1 && ImGui::IsKeyPressed(ImGuiKey_GamepadFaceRight)) {
				fadeto((2 * FPS / 30), 1);
			}
		}
		ImGui::End();
		ImGui::PopStyleVar(1);
		style->Colors[ImGuiCol_Text].w = og.w;
	}
};


inline scrolltextbox scrolltest = scrolltextbox(&testslice, "scrolltextboxtest", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eget mollis lorem, malesuada hendrerit diam. In imperdiet ligula nec tristique egestas. Vivamus semper nisl nec metus facilisis, non imperdiet odio suscipit. Phasellus est risus, pellentesque vitae enim a, pellentesque aliquet felis. Etiam et placerat augue, ac mattis augue. Praesent lacinia nisl nec dui pharetra, et eleifend lectus euismod. Suspendisse vitae justo pulvinar, rutrum nisi et, suscipit risus. Praesent facilisis rutrum lacus, sit amet imperdiet libero aliquam non. Aenean bibendum malesuada est, eget laoreet turpis lobortis quis. Pellentesque in lectus et magna viverra lacinia vel sit amet elit. Pellentesque feugiat arcu ut blandit convallis. Duis ultrices diam ipsum, vel ornare quam dictum quis.\nAliquam eu fringilla ipsum, nec gravida nisl.Sed consequat dolor ut facilisis dignissim.Donec et metus neque. Sed scelerisque leo vel justo interdum finibus.Nunc mollis justo ultrices est volutpat cursus.Maecenas sit amet scelerisque massa.Mauris nunc velit, laoreet id auctor sit amet, tristique vitae purus.Integer efficitur laoreet nisi eu interdum.Suspendisse fermentum nibh enim, eu interdum odio mollis a.Duis tempus erat ac ipsum egestas sagittis.Nunc imperdiet mauris vel massa interdum, condimentum dapibus dui vestibulum.Sed at scelerisque purus.Nulla rutrum non enim vel vehicula.Nulla varius sapien ac consectetur blandit.	\nNam et dapibus dui.Pellentesque volutpat, nisl id accumsan tincidunt, nulla erat malesuada nulla, nec tincidunt mauris sem quis sem.Vestibulum eu vestibulum elit.Donec vel placerat lorem, sit amet ultrices velit.Curabitur tincidunt mollis quam a eleifend.Maecenas dictum congue ex, id pellentesque enim commodo sit amet.In ultricies quam in tincidunt vehicula.Sed massa quam, ultrices vel nisi sit amet, elementum sodales felis.Donec placerat lacus a tortor fermentum mollis.Pellentesque tincidunt vulputate leo non mattis.\nNulla pretium massa quis odio tincidunt vulputate.Maecenas aliquam commodo lorem non blandit.Nunc mollis nulla id tempor porta.In ligula augue, ornare et venenatis vel, luctus ut lacus.Donec a pretium odio.Nam eleifend dui et purus accumsan feugiat.In dictum ex eu consequat viverra.Sed nec est ut lorem consectetur cursus.Curabitur vitae sollicitudin diam.Suspendisse viverra ultrices ex vitae vulputate.\nVivamus felis augue, tincidunt id elit ac, laoreet semper mi.Sed tortor quam, hendrerit quis justo a, fermentum maximus nibh.Cras justo lacus, ultricies at placerat sit amet, interdum in nulla.Donec convallis nibh leo, at suscipit magna egestas molestie.Integer arcu tortor, faucibus sed cursus a, rutrum venenatis diam.Suspendisse potenti.Praesent sagittis nisi magna, id accumsan tellus euismod at.Aliquam ut justo nibh.Morbi molestie lacinia nisl, sed posuere ligula fermentum id.Nam id tincidunt nisi.Quisque vel malesuada orci. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eget mollis lorem, malesuada hendrerit diam. In imperdiet ligula nec tristique egestas. Vivamus semper nisl nec metus facilis Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eget mollis lorem, malesuada hendrerit diam. In imperdiet ligula nec tristique egestas. Vivamus semper nisl nec metus facilisis, non imperdiet odio suscipit. Phasellus est risus, pellentesque vitae enim a, pellentesque aliquet felis. Etiam et placerat augue, ac mattis augue. Praesent lacinia nisl nec dui pharetra, et eleifend lectus euismod. Suspendisse vitae justo pulvinar, rutrum nisi et, suscipit risus. Praesent facilisis rutrum lacus, sit amet imperdiet libero aliquam non. Aenean bibendum malesuada est, eget laoreet turpis lobortis quis. Pellentesque in lectus et magna viverra lacinia vel sit amet elit. Pellentesque feugiat arcu ut blandit convallis. Duis ultrices diam ipsum, vel ornare quam dictum quis.\nAliquam eu fringilla ipsum, nec gravida nisl.Sed consequat dolor ut facilisis dignissim.Donec et metus neque. Sed scelerisque leo vel justo interdum finibus.Nunc mollis justo ultrices est volutpat cursus.Maecenas sit amet scelerisque massa.Mauris nunc velit, laoreet id auctor sit amet, tristique vitae purus.Integer efficitur laoreet nisi eu interdum.Suspendisse fermentum nibh enim, eu interdum odio mollis a.Duis tempus erat ac ipsum egestas sagittis.Nunc imperdiet mauris vel massa interdum, condimentum dapibus dui vestibulum.Sed at scelerisque purus.Nulla rutrum non enim vel vehicula.Nulla varius sapien ac consectetur blandit.	\nNam et dapibus dui.Pellentesque volutpat, nisl id accumsan tincidunt, nulla erat malesuada nulla, nec tincidunt mauris sem quis sem.Vestibulum eu vestibulum elit.Donec vel placerat lorem, sit amet ultrices velit.Curabitur tincidunt mollis quam a eleifend.Maecenas dictum congue ex, id pellentesque enim commodo sit amet.In ultricies quam in tincidunt vehicula.Sed massa quam, ultrices vel nisi sit amet, elementum sodales felis.Donec placerat lacus a tortor fermentum mollis.Pellentesque tincidunt vulputate leo non mattis.\nNulla pretium massa quis odio tincidunt vulputate.Maecenas aliquam commodo lorem non blandit.Nunc mollis nulla id tempor porta.In ligula augue, ornare et venenatis vel, luctus ut lacus.Donec a pretium odio.Nam eleifend dui et purus accumsan feugiat.In dictum ex eu consequat viverra.Sed nec est ut lorem consectetur cursus.Curabitur vitae sollicitudin diam.Suspendisse viverra ultrices ex vitae vulputate.\nVivamus felis augue, tincidunt id elit ac, laoreet semper mi.Sed tortor quam, hendrerit quis justo a, fermentum maximus nibh.Cras justo lacus, ultricies at placerat sit amet, interdum in nulla.Donec convallis nibh leo, at suscipit magna egestas molestie.Integer arcu tortor, faucibus sed cursus a, rutrum venenatis diam.Suspendisse potenti.Praesent sagittis nisi magna, id accumsan tellus euismod at.Aliquam ut justo nibh.Morbi molestie lacinia nisl, sed posuere ligula fermentum id.Nam id tincidunt nisi.Quisque vel malesuada orci. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean eget mollis lorem, malesuada hendrerit diam. In imperdiet ligula nec tristique egestas. Vivamus semper nisl nec metus facilis", 100, 15);