#pragma once
#include "Parished.h"

class CHooking {
public:
	CHooking();
	~CHooking();
	virtual void Jump(uint32_t address, uint32_t function);
	virtual void CreateDetour(uint32_t address, uint32_t stub_func, uint32_t hook_func);
	virtual void CreateGPLRDetour(uint32_t address, uint32_t stub_func, uint32_t hook_func, uint32_t gplr_1, uint32_t gplr_2, uint32_t gplr_3, uint32_t gplr_4);

	virtual uint32_t BranchLinked(uint32_t address, uint32_t function);

	virtual void DeleteDetour(uint32_t address, uint32_t stub_func);
	virtual void DeleteGPLRDetour(uint32_t address, uint32_t stub_func, uint32_t gplr_1, uint32_t gplr_2, uint32_t gplr_3, uint32_t gplr_4);

	virtual bool bCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask);
	virtual uint32_t FindPattern(uint32_t dwAddress, unsigned long dwLen, unsigned char* bMask, char* szMask);
};

