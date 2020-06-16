#pragma once
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/process.h>

#include "structures.h"
#include "funcs.h"
#include "utility.h"
#include "hooking.h"
#include "hooks.h"
#include "hudelems.h"
#include "menu.h"
#include "menufuncs.h"

extern "C" {
	void * _sys_malloc(int size);
	int _sys_free(void * mem);
	void* _sys_memset(void* m, int c, size_t n);
}

