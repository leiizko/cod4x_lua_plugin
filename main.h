#ifndef MAIN_H
#define MAIN_H

#include "../pinc.h"
#include "inc/lua.h"
#include "inc/lualib.h"
#include "inc/lauxlib.h"
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
	#include <memoryapi.h>
#else
	#include <sys/mman.h>
#endif

#define ALIGNMENT 0x1000
#define MAX_FUNCTIONS 0x40
#define STUB_SIZE 0x20
#define PLUGIN_VERSION_MAJOR 0
#define PLUGIN_VERSION_MINOR 4

typedef unsigned int long DWORD;

extern lua_State *LuaVM;
extern char *AllocMem;
extern int definedFunctions;

int Lua_TraceBack( lua_State* L );
int Plugin_Lua_pcall( lua_State* L, int nargs, int nret );
void Global_LuaHandler( char *funcName );

void *aligned_malloc( int size, int ALIGN );
char *AllocStub( char *funcName );
DWORD SetCall(DWORD addr, void* destination);

#endif // MAIN_H