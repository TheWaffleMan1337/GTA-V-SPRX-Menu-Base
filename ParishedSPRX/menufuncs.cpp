#include "menufuncs.h"


void EnterMenu(int menuId) {
	self->BackgroundShader->ScaleOverTime(0.25f, 400, 90 + (self->MaxScroll[MainMenu] * 25));
	for (int i = 0; i < self->MaxScroll[self->CurrentMenu]; i++) {
		//self->Options[i] = CreateText(menu[self->CurrentMenu][i].text, self->screen.width - 390, 140 + (25 * i), 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_BOTTOM, ALIGN_LEFT);
		self->Options[i]->FadeOverTime(0.45f, color_s(0, 0, 0, 0));
		self->Options[i]->Free();


		if (menu[self->CurrentMenu][i].isSlider) {
			self->SliderOpts[i]->FadeOverTime(0.45f, color_s(0, 0, 0, 0));
			self->SliderOpts[i]->Free();
		}

	}

	self->CurrentOption = 0;
	self->CurrentMenu = menuId;

	for (int i = 0; i < self->MaxScroll[menuId]; i++) {
		self->Options[i] = CreateText(menu[menuId][i].text, (self->screen.width / 2) - 150, 140 + (25 * i), 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_LEFT);
		self->Options[i]->FadeOverTime(0.45f, color_s(255, 255, 255, 255));

		if (menu[self->CurrentMenu][i].isSlider) {
			self->SliderOpts[i] = CreateText(menu[MainMenu][i].sliderText, (self->screen.width / 2) + 150, 140 + (25 * i), 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_RIGHT);
			self->SliderOpts[i]->FadeOverTime(0.45f, color_s(255, 255, 255, 255));
		}

	}

	self->CreatorText->text = menu[menuId][0].title;

	self->ScrollbarShader->MoveOverTime(0.25f, self->ScrollbarShader->x, 153.0f + (self->CurrentOption * 25));
}
