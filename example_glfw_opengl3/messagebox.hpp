#pragma once

#include "textbox.hpp"
#include "sound.hpp"
class messagebox : public textbox {
public:
	float FPS = 60;
	int truewidth;
	int trueheight;
	int truexpos;
	int trueypos;
	int timer = -1;
	int fadeouttime = -1;
	int choice = 0; //0 is nothing, 1 is to transparent, 2 is from transparent to box.
	float fadeincrement = 0;
	ImVec2 midpoint;
	bool usetp = false;
	ImVec2 temppoint;
	bool calculatedmp = false;
	void fadeto(int fadeduration, int choice) {
		fadeincrement = 1.0f / (float)fadeduration;
		this->choice = choice;
		switch (choice) {
		case 1:
			sound::play();
			break;
		case 2:
			sound::play2();
			break;
		}
	}
	void start(int fadeouttime) {
		this->fadeouttime = fadeouttime;
		fadeto((3 * FPS / 30), 2);
		timer = 0;
	}
	messagebox() {

	}
	messagebox(nineslice* slice, std::string name, std::string text) {
		box = slice;
		this->name = name;
		this->text = text;
		this->transparency = 0.0f;
		this->texttransparency = 0.0f;
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
		textbox::Begin();
		if (!calculatedmp) {
			truewidth = width;
			trueheight = height;
			truexpos = xpos;
			trueypos = ypos;
			midpoint = ImVec2(truexpos + (truewidth * 0.5f), trueypos + (trueheight * 0.5f));
			calculatedmp = true;
		}
		if (timer != -1)
			timer++;
	}
};

inline messagebox messagetest = messagebox(&testslice, "asdfasdf", "Hope you all are doing well,\nI'm not done with modding just yet.");