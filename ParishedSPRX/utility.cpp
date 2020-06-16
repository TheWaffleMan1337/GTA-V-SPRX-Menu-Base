#include "utility.h"


int printf_t[2] = { 0x014FDC5C, 0x01C85330 };
void(*printf)(const char *fmt, ...) = (void(*)(const char *, ...))&printf_t;

char * strcat(char * destination, const char * source) {
	int toc_t[2] = { 0x014FCE80, 0x01C85330 };
	char*(*temp)(char * r3, const char * r4) = (char*(*)(char *, const char *))&toc_t;
	return temp(destination, source);
}
int strcmp(const char * str1, const char * str2) {
	int toc_t[2] = { 0x014FD1B8, 0x01C85330 };
	return ((int(*)(const char *, const char *))&toc_t)(str1, str2);
}

//
void * operator new(size_t _Size) {
	return _sys_malloc(_Size);
}

void * operator new[](size_t _Size) {
	return _sys_malloc(_Size);
}

void operator delete(void * r3) {
	_sys_free(r3);
}

void operator delete[](void * r3) {
	_sys_free(r3);
}


int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size) {
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size) {
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size) {
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size) {
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}

CUtility::CUtility() {
	hooks = new CHooking();
}

CUtility::~CUtility() {
	
}


void CUtility::write_memory(uint64_t ea, const void* data, size_t size) {
	sys_dbg_write_process_memory(ea, data, size);
	sys_dbg_write_process_memory_ps3mapi(ea, data, size);
}
void CUtility::read_memory(uint64_t ea, void* data, size_t size) {
	sys_dbg_read_process_memory(ea, data, size);
}
void CUtility::read_memory_hen(uint64_t ea, void* data, size_t size) {
	sys_dbg_read_process_memory_ps3mapi(ea, data, size);
}


void CUtility::OnLoad() {
	hudelems = (hudelem_s*)(0x10040000);

	//hooks->CreateGPLRDetour(0x011896F4, *(uint32_t*)(sub_11896F4_Stub), *(uint32_t*)(sub_11896F4_Hook), 0, 0x0150AA84, 0, 0); //unknown function
	//hooks->CreateGPLRDetour(0x012C8D60, *(uint32_t*)(Scripted_Game_Event_Stub), *(uint32_t*)(Scripted_Game_Event_Hook), 0, 0x0150AA78, 0, 0); //network script event hook for doing stuff
	hooks->CreateGPLRDetour(0x009B4D00, *(uint32_t*)(VM_Stub), *(uint32_t*)(VM_Hook), 0, 0x0150AA58, 0, 0); //RageVM hook (main hook)
	//hooks->CreateGPLRDetour(0x00D914CC, *(uint32_t*)(GetLocalizedString_Stub), *(uint32_t*)(GetLocalizedString_Hook), 0, 0x0150AA88, 0, 0); //localized string hook to change strings to my own
	//hooks->Jump(0x003E3A20, *(uint32_t*)(IS_PLAYER_ONLINE)); //random patch because why not
}

void CUtility::OnUnLoad() {
	
	_sys_memset(self, 0, sizeof(Self));

	//hooks->DeleteGPLRDetour(0x011896F4, *(uint32_t*)(sub_11896F4_Stub), 0, 0x0150AA84, 0, 0);
	//hooks->DeleteGPLRDetour(0x012C8D60, *(uint32_t*)(Scripted_Game_Event_Stub), 0, 0x0150AA78, 0, 0);
	hooks->DeleteGPLRDetour(0x009B4D00, *(uint32_t*)(VM_Stub), 0, 0x0150AA58, 0, 0);
	//hooks->DeleteGPLRDetour(0x00D914CC, *(uint32_t*)(GetLocalizedString_Stub), 0, 0x0150AA88, 0, 0);
	//write_memory(0x003E3A20, (const void*)"\xF8\x21\xFF\x91\x7C\x08\x02\xA6\xF8\x01\x00\x80\x38\x60\x00\x01", 0x10);
}
