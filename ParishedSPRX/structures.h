#pragma once
#include "Parished.h"

enum eButtons_t {
	BUTTON_A = 0xC1,
	BUTTON_B = 0xC3,
	BUTTON_X = 0xC2,
	BUTTON_Y = 0xC0,
	BUTTON_BACK = 0xBF,
	BUTTON_LSHLDR = 0xC4,
	BUTTON_LTRIG = 0xC6,
	BUTTON_LSTICK = 0xC8,
	BUTTON_RSHLDR = 0xC5,
	BUTTON_RTRIG = 0xC7,
	BUTTON_RSTICK = 0xC9,
	DPAD_UP = 0xCA,
	DPAD_DOWN = 0xCB,
	DPAD_LEFT = 0xCC,
	DPAD_RIGHT = 0xCD
};

struct Menu;
struct hudelem_s;

struct Screen {
	int width;
	int height;
};

struct WaitSystem {
	int iTick;
	int iWait;
	virtual bool IsReady();
	virtual void Sleep(float time);
};

struct Self {
	Self();
	~Self();
	Screen screen;
	WaitSystem renderer;

	int MaxScroll[20];
	bool isMenuOpen;
	int CurrentOption;
	int CurrentMenu;

	hudelem_s * BackgroundShader;
	hudelem_s * LeftLineShader;
	hudelem_s * ScrollbarShader;
	hudelem_s * TitleText;
	hudelem_s * CreatorText;
	hudelem_s * Options[20];
	hudelem_s * SliderOpts[20];


	virtual void AddTitle(int menuIndex, int topMenu, const char * title);
	virtual void AddOption(int menuIndex, const char * opt, void(*func)());
	virtual void AddOption(int menuIndex, const char * opt, void(*func)(const char * arg), const char * arg);
	virtual void AddOption(int menuIndex, const char * opt, void(*func)(int arg), int arg);
	virtual void AddSlider(int menuIndex, const char * opt, float curVal, float minVal, float maxVal, float scaleVal, char ** strings, void(*func)(float val));
	virtual void SetupMenus();
	virtual void SetupControls();

};

struct g_pLocalPlayer_t {
	char __padding000[0x0070];
	float origin[3];
	char __padding001[0x0038];
	int invulnerability;
	char __padding002[0x00B8];
	float health;
	float maxhealth;
};

struct g_pWorld_t {
	char __padding000[0x0004];
	g_pLocalPlayer_t * pLocalPlayer;
};

extern g_pWorld_t * g_pWorld;
extern Self * self;