#pragma once
#include "Parished.h"

template <typename T>extern inline T(*Call(unsigned int address))(...);
template<typename R, typename... Arguments> inline R VariadicCall(long long function, Arguments... args);
enum eAlign_t;

void UI_DrawShader(float x, float y, float w, float h, int r, int g, int b, int a, eAlign_t vertAlign, eAlign_t horzAlign);
void UI_DrawText(const char * text, float x, float y, float scale, int font, int r, int g, int b, int a, eAlign_t vertAlign, eAlign_t horzAlign);
void DRAW_RECT(float x, float y, float w, float h, int r, int g, int b, int a);
float GET_TEXT_SCALE_HEIGHT(float size, int font);
void END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y);
void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char * text);
void BEGIN_TEXT_COMMAND_WIDTH(const char * text);
float END_TEXT_COMMAND_GET_WIDTH(bool r3);
void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char * text);
float GetTextWidth(const char *text, int font, float scale);
float GetTextHeight(int font, float scale);
void SET_TEXT_FONT(int fontType);
void SET_TEXT_SCALE(float r3, float scale);
void SET_TEXT_COLOR(int r, int g, int b, int a);
void SET_TEXT_WRAP(float start, float end);
void GET_SCREEN_RESOLUTION(int * width, int * height);
void DISABLE_CONTROL_ACTION(int inputGroup, int control);
bool IS_DISABLED_CONTROL_JUST_PRESSED(int inputGroup, int control);
bool IS_CONTROL_PRESSED(int inputGroup, int control);
int GET_RANDOM_INT_IN_RANGE(int min, int max);
void BEGIN_TEXT_COMMAND_THEFEED_POST(const char * text);
void DRAW_NOTIFICATION(bool r3, bool r4);
void SET_NOTIFICATION_TEXT_ENTRY(const char * text);
void BEGIN_TEXT_COMMAND_PRINT(const char * str);
void END_TEXT_COMMAND_PRINT(int duration, bool drawNow);

void GAME_NOTIFY_POPUP(const char * text);
void GAME_DRAW_SUBTITLE(const char * text);