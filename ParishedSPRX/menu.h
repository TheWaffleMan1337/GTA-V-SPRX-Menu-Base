#pragma once
#include "Parished.h"

struct Menu;

enum eMenus {
	MainMenu,
	SubMenu1,
};

enum CallType {
	CALL_NONE,
	CALL_STRING,
	CALL_INT,
	CALL_SLIDER,
};


struct Menu {
	int parentMenu;
	const char * title;
	const char * text;
	const char * sliderText;
	char ** sliderArray;
	void(*func0)();
	void(*func1)(const char * arg);
	void(*func2)(int arg);
	void(*func3)(float val);
	const char * func1arg;
	int func2arg;
	CallType calltype;
	bool isSlider;
	float minVal;
	float maxVal;
	float curVal;
	float scaleVal;
};

extern Menu menu[20][20];
