#include "structures.h"

Self::Self() {

}

Self::~Self() {

}

bool WaitSystem::IsReady() {
	return ((*(int*)(0x001EC672C) - iTick) >= iWait);
}

void WaitSystem::Sleep(float time) {
	iTick = *(int*)(0x001EC672C);
	iWait = (int)(time * 1000);
}

void Self::AddTitle(int menuIndex, int topMenu, const char * title) {
	menu[menuIndex][0].parentMenu = topMenu;
	menu[menuIndex][0].title = title;
}
void Self::AddOption(int menuIndex, const char * opt, void(*func)()) {
	menu[menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[menuIndex][MaxScroll[menuIndex]].func0 = func;
	menu[menuIndex][MaxScroll[menuIndex]].calltype = CALL_NONE;
	MaxScroll[menuIndex] += 1;
}
void Self::AddOption(int menuIndex, const char * opt, void(*func)(const char * arg), const char * arg) {
	menu[menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[menuIndex][MaxScroll[menuIndex]].func1 = func;
	menu[menuIndex][MaxScroll[menuIndex]].func1arg = arg;
	menu[menuIndex][MaxScroll[menuIndex]].calltype = CALL_STRING;
	MaxScroll[menuIndex] += 1;
}
void Self::AddOption(int menuIndex, const char * opt, void(*func)(int arg), int arg) {
	menu[menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[menuIndex][MaxScroll[menuIndex]].func2 = func;
	menu[menuIndex][MaxScroll[menuIndex]].func2arg = arg;
	menu[menuIndex][MaxScroll[menuIndex]].calltype = CALL_INT;
	MaxScroll[menuIndex] += 1;
}

void Self::AddSlider(int menuIndex, const char * opt, float curVal, float minVal, float maxVal, float scaleVal, char ** strings, void(*func)(float val)) {
	menu[menuIndex][MaxScroll[menuIndex]].text = opt;
	menu[menuIndex][MaxScroll[menuIndex]].func3 = func;
	menu[menuIndex][MaxScroll[menuIndex]].calltype = CALL_SLIDER;

	menu[menuIndex][MaxScroll[menuIndex]].sliderText = strings[(int)curVal];
	menu[menuIndex][MaxScroll[menuIndex]].sliderArray = strings;
	menu[menuIndex][MaxScroll[menuIndex]].isSlider = true;
	menu[menuIndex][MaxScroll[menuIndex]].curVal = curVal;
	menu[menuIndex][MaxScroll[menuIndex]].minVal = minVal;
	menu[menuIndex][MaxScroll[menuIndex]].maxVal = maxVal;
	menu[menuIndex][MaxScroll[menuIndex]].scaleVal = scaleVal;


	MaxScroll[menuIndex] += 1;
}

void testfloat(float test) {
	printf("%i\n", (int)test);
}
char * arrays[] = { "test 1", "test 2", "test 3", "test 4", "test 5", "test 6", "test 7", "test 8", "test 9" };
void testfunc() {}
void Self::SetupMenus() {
	for (int i = 0; i < 20;i++) {
		MaxScroll[i] = 0;
	}
	_sys_memset(menu, 0x00, sizeof(menu));
	AddTitle(MainMenu, MainMenu, "Main Menu");
	AddOption(MainMenu, "Sub Menu 1", EnterMenu, SubMenu1);
	AddOption(MainMenu, "Option 2", GAME_DRAW_SUBTITLE, "Option 2");
	AddOption(MainMenu, "Option 3", GAME_DRAW_SUBTITLE, "Option 3");
	AddOption(MainMenu, "Option 4", GAME_DRAW_SUBTITLE, "Option 4");
	AddOption(MainMenu, "Option 5", GAME_DRAW_SUBTITLE, "Option 5");
	AddOption(MainMenu, "Option 6", testfunc);
	AddOption(MainMenu, "Option 7", testfunc);
	AddSlider(MainMenu, "testing slider", 0, 0, 9, 1, arrays, testfloat);
	AddSlider(MainMenu, "testing slider", 0, 0, 9, 1, arrays, testfloat);
	

	AddTitle(SubMenu1, MainMenu, "Sub Menu 1");
	AddOption(SubMenu1, "Option 1", testfunc);
	AddOption(SubMenu1, "Option 2", testfunc);
	AddOption(SubMenu1, "Option 3", testfunc);
	AddSlider(SubMenu1, "testing slider", 0, 0, 9, 1, arrays, testfloat);
	AddSlider(SubMenu1, "testing slider", 0, 0, 9, 1, arrays, testfloat);

}


void Self::SetupControls() {

	if (!isMenuOpen) {
		if (IS_CONTROL_PRESSED(0, DPAD_DOWN) && IS_CONTROL_PRESSED(0, BUTTON_LTRIG)) {
			isMenuOpen = true;

			self->SetupMenus();
			self->BackgroundShader = CreateShader(self->screen.width / 2, 75, 400, 90, color_s(0, 0, 0, 0), ALIGN_TOP, ALIGN_LEFT);
			self->ScrollbarShader = CreateShader(self->screen.width / 2, 153.0f, 400, 18, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_LEFT);
			self->TitleText = CreateText("Menu Base", self->screen.width / 2, 75, 0.85f, 0, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_CENTER);
			self->CreatorText = CreateText(menu[MainMenu][0].title, self->screen.width /2, 115, 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_TOP, ALIGN_CENTER);


			self->BackgroundShader->FadeOverTime(0.25f, color_s(0, 0, 0, 180));
			self->ScrollbarShader->FadeOverTime(0.25f, color_s(255, 0, 0, 180));
			self->TitleText->FadeOverTime(0.25f, color_s(255, 255, 255, 255));
			self->CreatorText->FadeOverTime(0.25f, color_s(255, 255, 255, 255));

			//char option_buffer[0x500];
			//_sys_memset(option_buffer, 0x00, 0x1000);
			self->BackgroundShader->ScaleOverTime(0.25f, 400, 90 + (self->MaxScroll[MainMenu] * 25));
			for (int i = 0; i < MaxScroll[MainMenu]; i++) {
				self->Options[i] = CreateText(menu[MainMenu][i].text, (self->screen.width / 2) - 150, 140 + (25 * i), 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_LEFT);
				self->Options[i]->FadeOverTime(0.45f, color_s(255, 255, 255, 255));

				if (menu[self->CurrentMenu][i].isSlider) {
					self->SliderOpts[i] = CreateText(menu[MainMenu][i].sliderText, (self->screen.width / 2) + 150, 140 + (25 * i), 0.45f, 0, color_s(0, 0, 0, 0), ALIGN_CENTER, ALIGN_RIGHT);
					self->SliderOpts[i]->FadeOverTime(0.45f, color_s(255, 255, 255, 255));
				}

				//if (CurrentOption == i) {
				//	self->Options[i]->ScaleFontOverTime(0.15f, 0.52f);
				//	self->Options[i]->FadeOverTime(0.15f, color_s(GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), 255));
				//}
				//else {
				//	self->Options[i]->ScaleFontOverTime(0.15f, 0.45f);
				//	self->Options[i]->FadeOverTime(0.15f, color_s(255, 255, 255, 255));
				//}

			}

		}
	}
	else {
		DISABLE_CONTROL_ACTION(2, BUTTON_A);
		
		DISABLE_CONTROL_ACTION(2, DPAD_UP);
		DISABLE_CONTROL_ACTION(2, DPAD_DOWN);

		DISABLE_CONTROL_ACTION(2, DPAD_LEFT);
		DISABLE_CONTROL_ACTION(2, DPAD_RIGHT);

		DISABLE_CONTROL_ACTION(2, BUTTON_B);

		if (IS_DISABLED_CONTROL_JUST_PRESSED(2, DPAD_UP)) {
			//self->ScrollbarShader->SetPoint(self->ScrollbarShader->x, (float)(145.0f + (CurrentOption * 18.5f)));
			CurrentOption -= 1;


			if (CurrentOption < 0) {
				CurrentOption = MaxScroll[CurrentMenu] - 1;
			}

			//for (int i = 0; i < MaxScroll[CurrentMenu]; i++) {
			//	if (CurrentOption == i) {
			//		self->Options[i]->ScaleFontOverTime(0.15f, 0.52f);
			//		self->Options[i]->FadeOverTime(0.15f, color_s(GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), 255));
			//	}
			//	else {
			//		self->Options[i]->ScaleFontOverTime(0.15f, 0.45f);
			//		self->Options[i]->FadeOverTime(0.15f, color_s(255, 255, 255, 255));
			//	}
			//}

			self->ScrollbarShader->MoveOverTime(0.25f, self->ScrollbarShader->x, 153.0f + (CurrentOption * 25));
		}

		if (menu[self->CurrentMenu][self->CurrentOption].isSlider) {
			if (IS_DISABLED_CONTROL_JUST_PRESSED(2, DPAD_LEFT)) {
				menu[self->CurrentMenu][self->CurrentOption].curVal -= menu[self->CurrentMenu][self->CurrentOption].scaleVal;
				if (menu[self->CurrentMenu][self->CurrentOption].curVal < 0) {
					menu[self->CurrentMenu][self->CurrentOption].curVal = menu[self->CurrentMenu][self->CurrentOption].maxVal - 1;
				}
				self->SliderOpts[self->CurrentOption]->text = menu[self->CurrentMenu][self->CurrentOption].sliderArray[(int)menu[self->CurrentMenu][self->CurrentOption].curVal];
			}

			if (IS_DISABLED_CONTROL_JUST_PRESSED(2, DPAD_RIGHT)) {
				menu[self->CurrentMenu][self->CurrentOption].curVal += menu[self->CurrentMenu][self->CurrentOption].scaleVal;
				if (menu[self->CurrentMenu][self->CurrentOption].curVal > menu[self->CurrentMenu][self->CurrentOption].maxVal - 1) {
					menu[self->CurrentMenu][self->CurrentOption].curVal = 0;
				}
				self->SliderOpts[self->CurrentOption]->text = menu[self->CurrentMenu][self->CurrentOption].sliderArray[(int)menu[self->CurrentMenu][self->CurrentOption].curVal];
			}

			if (IS_DISABLED_CONTROL_JUST_PRESSED(2, BUTTON_A)) {
				menu[self->CurrentMenu][self->CurrentOption].func3(menu[self->CurrentMenu][self->CurrentOption].curVal);
			}

		}

		if (IS_DISABLED_CONTROL_JUST_PRESSED(2, DPAD_DOWN)) {

			CurrentOption += 1;

			if (CurrentOption > MaxScroll[CurrentMenu] - 1) {
				CurrentOption = 0;
			}

			//for (int i = 0; i < MaxScroll[CurrentMenu]; i++) {
			//	if (CurrentOption == i) {
			//		self->Options[i]->ScaleFontOverTime(0.15f, 0.52f);
			//		self->Options[i]->FadeOverTime(0.15f, color_s(GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), GET_RANDOM_INT_IN_RANGE(0, 255), 255));
			//	}
			//	else {
			//		self->Options[i]->ScaleFontOverTime(0.15f, 0.45f);
			//		self->Options[i]->FadeOverTime(0.15f, color_s(255, 255, 255, 255));
			//	}
			//}

			self->ScrollbarShader->MoveOverTime(0.25f, self->ScrollbarShader->x, 153.0f + (CurrentOption * 25));
		}

		if (IS_DISABLED_CONTROL_JUST_PRESSED(2, BUTTON_B)) {//driving meinsane on why it isnt working AHAAAAAAAAAAAAAA
			if (CurrentMenu == MainMenu) {
				isMenuOpen = false;
				self->BackgroundShader->type = HE_NONE;
				self->ScrollbarShader->type = HE_NONE;
				self->TitleText->type = HE_NONE;
				self->CreatorText->type = HE_NONE;
				for (int i = 0; i < MaxScroll[MainMenu]; i++) {
					self->Options[i]->type = HE_NONE;
					if (self->SliderOpts[i] != 0) {
						self->SliderOpts[i]->type = HE_NONE;
					}
				}
				//_sys_memset((void*)0x10040000, 0, 0x10000);
			}
			else {
				EnterMenu(menu[CurrentMenu]->parentMenu);
			}
		}
		if (IS_DISABLED_CONTROL_JUST_PRESSED(2, BUTTON_A)) {
			//self->ScrollbarShader->ScaleOverTime(0.25f, 400, 18);

			if (menu[CurrentMenu][CurrentOption].calltype == CALL_NONE) {
				menu[CurrentMenu][CurrentOption].func0();
			}

			if (menu[CurrentMenu][CurrentOption].calltype == CALL_STRING) {
				menu[CurrentMenu][CurrentOption].func1(menu[CurrentMenu][CurrentOption].func1arg);
			}

			if (menu[CurrentMenu][CurrentOption].calltype == CALL_INT) {
				menu[CurrentMenu][CurrentOption].func2(menu[CurrentMenu][CurrentOption].func2arg);
			}

		}
		
	}
}
