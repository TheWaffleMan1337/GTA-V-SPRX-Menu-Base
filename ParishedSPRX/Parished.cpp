#include "Parished.h"

SYS_MODULE_INFO( ParishedSPRX, 0, 1, 1);
SYS_MODULE_START( _ParishedSPRX_prx_entry );
SYS_MODULE_STOP( _ParishedSPRX_prx_exit );
CUtility * ps3_util;



extern "C" int _ParishedSPRX_prx_entry(void) {
	ps3_util = new CUtility();
	self = new Self();
	ps3_util->OnLoad();
	
	return SYS_PRX_RESIDENT;
}

extern "C" int _ParishedSPRX_prx_exit(void) {
	
	ps3_util->OnUnLoad();

	delete ps3_util->hooks;
	delete ps3_util;
	delete self;

	return SYS_PRX_RESIDENT;
}

