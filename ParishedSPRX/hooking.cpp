#include "hooking.h"

CHooking::CHooking() {

}

CHooking::~CHooking() {

}

void CHooking::Jump(uint32_t address, uint32_t function) {
	int FuncBytes[4];
	FuncBytes[0] = 0x3D600000 + ((function >> 16) & 0xFFFF);
	if (function & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (function & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	ps3_util->write_memory(address, FuncBytes, 0x10);
}

void CHooking::CreateDetour(uint32_t address, uint32_t stub_func, uint32_t hook_func) {
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	ps3_util->read_memory_hen(address, normalFunctionStub, 0x10);
	ps3_util->read_memory(address, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	ps3_util->write_memory(hook_func, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((stub_func >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (stub_func & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	ps3_util->write_memory(address, hookFunctionStub, 0x10);
}

uint32_t CHooking::BranchLinked(uint32_t address, uint32_t function) {
	uint32_t branch;
	if (function > address)
		branch = 0x48000001 + (function - address);
	else
		branch = 0x4C000001 - (address - function);
	return branch;
}

void CHooking::CreateGPLRDetour(uint32_t address, uint32_t stub_func, uint32_t hook_func, uint32_t gplr_1, uint32_t gplr_2, uint32_t gplr_3, uint32_t gplr_4) {
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	ps3_util->read_memory_hen(address, normalFunctionStub, 0x10);
	ps3_util->read_memory(address, normalFunctionStub, 0x10);
	if (gplr_1 != 0) { normalFunctionStub[0] = BranchLinked(stub_func + 0x00, gplr_1); }
	if (gplr_2 != 0) { normalFunctionStub[1] = BranchLinked(stub_func + 0x04, gplr_2); }
	if (gplr_3 != 0) { normalFunctionStub[2] = BranchLinked(stub_func + 0x08, gplr_3); }
	if (gplr_4 != 0) { normalFunctionStub[3] = BranchLinked(stub_func + 0x0C, gplr_4); }
	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	ps3_util->write_memory(stub_func, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((hook_func >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (hook_func & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	ps3_util->write_memory(address, hookFunctionStub, 0x10);
}

void CHooking::DeleteDetour(uint32_t address, uint32_t stub_func) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory(stub_func, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(address, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(stub_func, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(address, normalFunctionStub, 0x10);
}

void CHooking::DeleteGPLRDetour(uint32_t address, uint32_t stub_func, uint32_t gplr_1, uint32_t gplr_2, uint32_t gplr_3, uint32_t gplr_4) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(stub_func, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(stub_func, normalFunctionStub, 0x10);
	if (gplr_1 != 0) { normalFunctionStub[0] = BranchLinked(address + 0x00, gplr_1); }
	if (gplr_2 != 0) { normalFunctionStub[1] = BranchLinked(address + 0x04, gplr_2); }
	if (gplr_3 != 0) { normalFunctionStub[2] = BranchLinked(address + 0x08, gplr_3); }
	if (gplr_4 != 0) { normalFunctionStub[3] = BranchLinked(address + 0x0C, gplr_4); }
	ps3_util->write_memory(address, normalFunctionStub, 0x10);
}

bool CHooking::bCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;

	return (*szMask) == 0;
}

uint32_t CHooking::FindPattern(uint32_t dwAddress, unsigned long dwLen, unsigned char* bMask, char* szMask) {
	for (uint32_t i = 0; i < dwLen; i++)
		if (bCompare((unsigned char*)(dwAddress + i), bMask, szMask))
			return (uint32_t)(dwAddress + i);

	return 0;
}
