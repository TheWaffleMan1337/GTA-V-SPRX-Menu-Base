#pragma once
#include "Parished.h"
class CHooking;

extern int printf_t[2];
extern void(*printf)(const char * fmt, ...);

char * strcat(char * destination, const char * source);
int strcmp(const char * str1, const char * str2);

void* operator new(size_t _Size);
void* operator new[](size_t _Size);

void operator delete(void * r3);
void operator delete[](void * r3);

int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size);
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size);
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size);
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size);

class CUtility {
public:
	CUtility();
	~CUtility();
	CHooking * hooks;

	virtual void OnLoad();
	virtual void OnUnLoad();

	virtual void write_memory(uint64_t ea, const void* data, size_t size);
	virtual void read_memory(uint64_t ea, void* data, size_t size);
	virtual void read_memory_hen(uint64_t ea, void* data, size_t size);

};

extern CUtility * ps3_util;

