#include "hooks.h"

g_pWorld_t * g_pWorld;
Self * self;



void VM_Stub(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
void VM_Hook(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6) {
	GET_SCREEN_RESOLUTION(&self->screen.width, &self->screen.height);
	hudelems = (hudelem_s*)(0x10040000);
	if (self->renderer.IsReady()) {

		//for (int i = 0; i < self->MaxScroll[self->CurrentMenu];i++) {
		//	if (menu[self->CurrentMenu][i].isSlider) {
		//
		//	}
		//}

		RenderHuds();

		self->SetupControls();

		self->renderer.Sleep(0.001f);
	}

	//printf("width: %i - height: %i\n", self->screen.width, self->screen.height);
	g_pWorld = *(g_pWorld_t**)(0x01CEFCF8);
	//printf("virtual machine hooked\n");

	if (g_pWorld) {
		if (g_pWorld->pLocalPlayer) {
			//printf("0x%X\n", g_pWorld->pLocalPlayer);
			g_pWorld->pLocalPlayer->health = g_pWorld->pLocalPlayer->maxhealth;
		}
	}

	VM_Stub(r3, r4, r5, r6);
}
