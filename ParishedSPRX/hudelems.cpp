#include "hudelems.h"

hudelem_s *hudelems;

hudelem_s * HudElem_Alloc() {
	for (int i = 0; i < 200; i++) {
		if (hudelems[i].type == HE_NONE) {
			return &hudelems[i];
		}
	}
	return 0;
}

void RenderHuds() {
	for (int i = 0; i < 200; i++) {
		if (hudelems[i].type != HE_NONE) {
			if (hudelems[i].type == HE_TEXT) {
				UI_DrawText(hudelems[i].text, hudelems[i].x, hudelems[i].y, hudelems[i].fontScale, hudelems[i].font, hudelems[i].color.r, hudelems[i].color.g, hudelems[i].color.b, hudelems[i].color.a, hudelems[i].vertAlign, hudelems[i].horzAlign);
				ScaleFontOverTime(hudelems[i].startFontScaleTime, hudelems[i].scaleTime, hudelems[i].fontScaleFrom, hudelems[i].fontScaleTo, &hudelems[i].fontScale);
			}
			if (hudelems[i].type == HE_SHADER) {
				UI_DrawShader(hudelems[i].x, hudelems[i].y, hudelems[i].width, hudelems[i].height, hudelems[i].color.r, hudelems[i].color.g, hudelems[i].color.b, hudelems[i].color.a, hudelems[i].vertAlign, hudelems[i].horzAlign);
				ScaleOverTime(hudelems[i].startScaleOverTime, hudelems[i].scaleTime, hudelems[i].width, hudelems[i].height, hudelems[i].toWidth, hudelems[i].toHeight, &hudelems[i].width, &hudelems[i].height);
			}
			MoveOverTime(hudelems[i].startTime, hudelems[i].moveTime, hudelems[i].fromX, hudelems[i].fromY, hudelems[i].toX, hudelems[i].toY, &hudelems[i].x, &hudelems[i].y);
			FadeOverTime(hudelems[i].startFadeScaleTime, hudelems[i].fadeTime, hudelems[i].fromColor.r, hudelems[i].fromColor.g, hudelems[i].fromColor.b, hudelems[i].fromColor.a, hudelems[i].toColor.r, hudelems[i].toColor.g, hudelems[i].toColor.b, hudelems[i].toColor.a, &hudelems[i].color.r, &hudelems[i].color.g, &hudelems[i].color.b, &hudelems[i].color.a);
		}
	}
}


void FadeOverTime(int StartTime, int FadeTime, int fromR, int fromG, int fromB, int fromA, int toR, int toG, int toB, int toA, int * outR, int * outG, int * outB, int * outA) {
	int TimeTaken = *(int*)(0x001EC672C) - StartTime;
	if (TimeTaken > FadeTime) {
		*outR = toR;
		*outG = toG;
		*outB = toB;
		*outA = toA;
		return;
	}
	if (TimeTaken < 0)
		TimeTaken = 0;

	float Lerp = (float)TimeTaken / (float)FadeTime;
	*outR = (((toR - fromR) * Lerp) + fromR);
	*outG = (((toG - fromG) * Lerp) + fromG);
	*outB = (((toB - fromB) * Lerp) + fromB);
	*outA = (((toA - fromA) * Lerp) + fromA);
}
void ScaleOverTime(int StartTime, int ScaleTime, float fromWidth, float fromHeight, float toWidth, float toHeight, float * outWidth, float * outHeight) {
	int TimeTaken = *(int*)(0x001EC672C) - StartTime;
	if (TimeTaken > ScaleTime) {
		TimeTaken = ScaleTime;
	}
	if (TimeTaken < 0)
		TimeTaken = 0;

	float Lerp = (float)TimeTaken / (float)ScaleTime;
	*outWidth = (((toWidth - fromWidth) * Lerp) + fromWidth);
	*outHeight = (((toHeight - fromHeight) * Lerp) + fromHeight);

}
void ScaleFontOverTime(int StartTime, int ScaleTime, float fromScale, float ToScale, float *outScale) {
	int TimeTaken = *(int*)(0x001EC672C) - StartTime;
	if (TimeTaken > ScaleTime) {
		TimeTaken = ScaleTime;
	}
	if (TimeTaken < 0)
		TimeTaken = 0;

	float Lerp = (float)TimeTaken / (float)ScaleTime;
	*outScale = (((ToScale - fromScale) * Lerp) + fromScale);
}
void MoveOverTime(int StartTime, int FadeTime, float xFromCoord, float yFromCoord, float xToCoord, float yToCoord, float* xOutput, float* yOutput) {
	int TimeTaken = *(int*)(0x001EC672C) - StartTime;
	if (TimeTaken > FadeTime) {
		*xOutput = xToCoord;
		*yOutput = yToCoord;
		return;
	}
	if (TimeTaken < 0)
		TimeTaken = 0;

	float Lerp = (float)TimeTaken / (float)FadeTime;
	*xOutput = (((xToCoord - xFromCoord) * Lerp) + xFromCoord);
	*yOutput = (((yToCoord - yFromCoord) * Lerp) + yFromCoord);
}


hudelem_s * CreateShader(float x, float y, float width, float height, color_s color, eAlign_t vertAlign, eAlign_t horzAlign) {
	hudelem_s *hudElem = HudElem_Alloc();
	hudElem->type = HE_SHADER;
	hudElem->toX = x;
	hudElem->toY = y;
	hudElem->fromX = hudElem->x;
	hudElem->fromY = hudElem->y;
	hudElem->startTime = *(int*)(0x001EC672C);
	hudElem->moveTime = 0;
	hudElem->scaleTime = 5;
	hudElem->toWidth = width;
	hudElem->toHeight = height;
	hudElem->width = width;
	hudElem->height = height;
	hudElem->fromWidth = width;
	hudElem->fromHeight = height;
	hudElem->color = color;
	hudElem->fromColor = color;
	hudElem->toColor = color;
	hudElem->vertAlign = vertAlign;
	hudElem->horzAlign = horzAlign;
	return hudElem;
}

hudelem_s * CreateText(const char * text, float x, float y, float fontScale, int font, color_s color, eAlign_t vertAlign, eAlign_t horzAlign) {
	hudelem_s *hudElem = HudElem_Alloc();
	hudElem->type = HE_TEXT;
	hudElem->text = text;
	hudElem->fontScale = fontScale;
	hudElem->fontScaleFrom = fontScale - 0.1f;
	hudElem->fontScaleTo = fontScale;
	hudElem->toX = x;
	hudElem->toY = y;
	hudElem->fromX = x;
	hudElem->fromY = y;
	hudElem->startTime = *(int*)(0x001EC672C);
	hudElem->scaleTime = 100;
	hudElem->color = color;
	hudElem->fromColor = color;
	hudElem->toColor = color;
	hudElem->vertAlign = vertAlign;
	hudElem->horzAlign = horzAlign;
	hudElem->font = font;
	return hudElem;
}

void hudelem_s::SetPoint(float x, float y) {
	this->toX = x;
	this->toY = y;
	this->fromX = x;
	this->fromY = y;
	this->x = x;
	this->y = y;
}

void hudelem_s::MoveOverTime(float time, float x, float y) {
	this->toX = x;
	this->toY = y;
	this->fromX = this->x;
	this->fromY = this->y;
	this->startTime = *(int*)(0x001EC672C);
	this->moveTime = (int)((1000 * time) + 0.5f);
}

void hudelem_s::FadeOverTime(float time, color_s color) {
	this->toColor = color;
	this->fromColor = this->color;
	this->startFadeScaleTime = *(int*)(0x001EC672C);
	this->fadeTime = (int)((1000 * time) + 0.5f);
}

void hudelem_s::ScaleOverTime(float time, float width, float height) {
	this->toWidth = width;
	this->toHeight = height;
	this->startScaleOverTime = *(int*)(0x001EC672C);
	this->scaleTime = (int)((1000 * time) + 0.5f);
}


void hudelem_s::ScaleFontOverTime(float time, float fontScale) {
	this->fontScaleFrom = this->fontScale;
	this->fontScaleTo = fontScale;
	this->startFontScaleTime = *(int*)(0x001EC672C);
	this->scaleTime = (int)((1000 * time) + 0.5f);
}

void hudelem_s::Free() {
	_sys_memset(this, 0x00, sizeof(hudelem_s));
}

