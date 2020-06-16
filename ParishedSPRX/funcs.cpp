#include "funcs.h"

template <typename T> inline T(*Call(unsigned int address))(...) {
	int opd[2] = { address, 0x01C85330 };
	T(*func)(...) = (T(*)(...))&opd;
	return func;
}

template<typename R, typename... Arguments> inline R VariadicCall(long long function, Arguments... args) {
	int toc_t[2] = { function, 0x01C85330 };
	R(*temp)(Arguments...) = (R(*)(Arguments...))&toc_t;
	return temp(args...);
}


void UI_DrawShader(float x, float y, float w, float h, int r, int g, int b, int a, eAlign_t vertAlign, eAlign_t horzAlign) {
	if (horzAlign == ALIGN_LEFT)
	{
		x = x;
	}
	if (horzAlign == ALIGN_RIGHT) {x -= x;
}
	if (horzAlign == ALIGN_CENTER) { x -= w / 2; }

	if (vertAlign == ALIGN_BOTTOM) { y -= h; }
	if (vertAlign == ALIGN_CENTER) { y -= h / 2; }


	DRAW_RECT(x / self->screen.width, y / self->screen.height + ((h / self->screen.height) / 2), w / self->screen.width, h / self->screen.height, r, g, b, a);
}

void UI_DrawText(const char * text, float x, float y, float scale, int font, int r, int g, int b, int a, eAlign_t vertAlign, eAlign_t horzAlign) {
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(scale, scale);
	SET_TEXT_COLOR(r, g, b, a);

	if (horzAlign == ALIGN_RIGHT) { x -= GetTextWidth(text, font, scale); }
	if (horzAlign == ALIGN_CENTER) { x -= (GetTextWidth(text, font, scale) / 2); }

	if (vertAlign == ALIGN_BOTTOM) { y -= GetTextHeight(font, scale); }
	if (vertAlign == ALIGN_CENTER) { y -= (GetTextHeight(font, scale) / 2); }
	BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	END_TEXT_COMMAND_DISPLAY_TEXT(x / self->screen.width, y / self->screen.height);
}

void DRAW_RECT(float x, float y, float w, float h, int r, int g, int b, int a) {
	Call<void>(0x003BFC98)(x, y, w, h, r, g, b, a);
}

float GET_TEXT_SCALE_HEIGHT(float size, int font) {
	return Call<float>(0x003C9678)(size, font);
}
void END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y) {
	Call<void>(0x003C82CC)(x, y);
}
void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char * text) {
	Call<void>(0x003C85D0)(text);
}

void BEGIN_TEXT_COMMAND_WIDTH(const char * text) {
	Call<void>(0x003C833C)(text);
}

float END_TEXT_COMMAND_GET_WIDTH(bool r3) {
	return Call<float>(0x003C835C)(r3);
}
void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char * text) {
	Call<void>(0x003C8294)(text);
}
float GetTextWidth(const char *text, int font, float scale) {
	BEGIN_TEXT_COMMAND_WIDTH("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(0.0f, scale);
	return (END_TEXT_COMMAND_GET_WIDTH(font) * self->screen.width);
}
float GetTextHeight(int font, float scale) {
	return GET_TEXT_SCALE_HEIGHT(scale, font);
}

void SET_TEXT_FONT(int fontType) {
	Call<void>(0x003C97EC)(fontType);
}
void SET_TEXT_SCALE(float r3, float scale) {
	Call<void>(0x003C9724)(r3, scale);
}
void SET_TEXT_COLOR(int r, int g, int b, int a) {
	Call<void>(0x003C9738)(r, g, b, a);
}
void SET_TEXT_WRAP(float start, float end) {
	Call<void>(0x003C97C4)(start, end);
}
void GET_SCREEN_RESOLUTION(int * width, int * height) {
	Call<void>(0x003C16C0)(width, height);
}
void DISABLE_CONTROL_ACTION(int inputGroup, int control) {
	Call<void>(0x00400D04)(inputGroup, control);
	Call<void>(0x00400C98)(inputGroup, control);
}

bool IS_DISABLED_CONTROL_JUST_PRESSED(int inputGroup, int control) {
	return Call<bool>(0x00400798)(inputGroup, control);
}

bool IS_CONTROL_PRESSED(int inputGroup, int control) {
	return Call<bool>(0x00400414)(inputGroup, control);
}

int GET_RANDOM_INT_IN_RANGE(int min, int max) {
	Call<int>(0x003D463C)(min, max);
}

void BEGIN_TEXT_COMMAND_THEFEED_POST(const char * text) {
	Call<void>(0x003C8018)(text);
}

void DRAW_NOTIFICATION(bool r3, bool r4) {
	Call<void>(0x003C8018)(r3, r4);
}

void SET_NOTIFICATION_TEXT_ENTRY(const char * text) {
	Call<void>(0x003C7E28)(text);
}

void BEGIN_TEXT_COMMAND_PRINT(const char * str) {
	Call<void>(0x003C8210)(str);
}

void END_TEXT_COMMAND_PRINT(int duration, bool drawNow) {
	Call<void>(0x003C8230)(duration, drawNow);
}

void GAME_NOTIFY_POPUP(const char * text) {
	SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	DRAW_NOTIFICATION(true, true);
}

void GAME_DRAW_SUBTITLE(const char * text) {
	BEGIN_TEXT_COMMAND_PRINT("STRING");
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	END_TEXT_COMMAND_PRINT(2000, true);
}

