#pragma once
#include "Parished.h"
//			   0x08  0xBD0
//CPedFactory->CPed->CPlayerInfo
union color_s {
	struct {
		int r, g, b, a;
	};

	color_s()
	{
		this->r = this->g = this->b = this->a = 0;
	}

	color_s(int r, int g, int b, int a) {
		this->r = r; this->g = g; this->b = b; this->a = a;
	}
};

enum eHudElemTypes_t {
	HE_NONE,
	HE_TEXT,
	HE_SHADER
};

enum eAlign_t {
	ALIGN_CENTER,
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_BOTTOM,
	ALIGN_TOP
};

struct hudelem_s {
	eHudElemTypes_t type;
	float x;
	float y;
	int font;
	const char * text;
	float fontScaleFrom;
	float fontScale;
	float fontScaleTo;
	int scaleTime;
	color_s fromColor;
	color_s color;
	color_s toColor;
	int fadeTime;
	float fromWidth;
	float fromHeight;
	float width;
	float height;
	float toWidth;
	float toHeight;
	eAlign_t horzAlign;
	eAlign_t vertAlign;
	float fromX;
	float fromY;
	float toX;
	float toY;
	int time;
	int moveTime;
	int startTime;
	int startFontScaleTime;
	int startFadeScaleTime;
	int startScaleOverTime;
	void SetPoint(float x, float y);
	void MoveOverTime(float time, float x, float y);
	void ScaleFontOverTime(float time, float fontScale);
	void ScaleOverTime(float time, float width, float height);
	void FadeOverTime(float time, color_s color);
	void Free();
};

void RenderHuds();

hudelem_s * CreateShader(float x, float y, float width, float height, color_s color, eAlign_t vertAlign, eAlign_t horzAlign);
hudelem_s * CreateText(const char * text, float x, float y, float fontScale, int font, color_s color, eAlign_t vertAlign, eAlign_t horzAlign);

void FadeOverTime(int StartTime, int FadeTime, int fromR, int fromG, int fromB, int fromA, int toR, int toG, int toB, int toA, int * outR, int * outG, int * outB, int * outA);
void ScaleOverTime(int StartTime, int ScaleTime, float fromWidth, float fromHeight, float toWidth, float toHeight, float * outWidth, float * outHeight);
void ScaleFontOverTime(int StartTime, int ScaleTime, float fromScale, float ToScale, float *outScale);
void MoveOverTime(int StartTime, int FadeTime, float xFromCoord, float yFromCoord, float xToCoord, float yToCoord, float* xOutput, float* yOutput);

extern  hudelem_s * hudelems;