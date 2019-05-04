#ifndef MAIN_H
#define MAIN_H

#include "../pinc.h"
#include "inc/lua.h"
#include "inc/lualib.h"
#include "inc/lauxlib.h"
#include <stdlib.h>

#ifdef _WIN32
	#include <memoryapi.h>
#else
	#include <sys/mman.h>
#endif

#define ALIGNMENT 0x1000
#define MAX_FUNCTIONS 0x40
#define STUB_SIZE 0x20
#define PLUGIN_VERSION_MAJOR 0
#define PLUGIN_VERSION_MINOR 2

typedef unsigned int long DWORD;

static lua_State *LuaVM;
static char *AllocMem = NULL;
static int definedFunctions = 0;

void Global_LuaHandler( char *funcName );
void registerFunctionsToLua();
static int Lua_TraceBack( lua_State* L );
static int Plugin_Lua_pcall( lua_State* L, int nargs, int nret );


// Register functions
static int Lua_Cmd_AddCommand( lua_State *L );
static int Lua_ScrAddFunction( lua_State *L );

// Add functions
static int Lua_Scr_AddEntity( lua_State *L );
static int Lua_Scr_AddInt( lua_State *L );
static int Lua_Scr_AddFloat( lua_State *L );
static int Lua_Scr_AddBool( lua_State *L );
static int Lua_Scr_AddString( lua_State *L );
static int Lua_Scr_AddUndefined( lua_State *L );
static int Lua_Scr_AddVector( lua_State *L );
static int Lua_Scr_AddArray( lua_State *L );
static int Lua_Scr_MakeArray( lua_State *L );
static int Lua_Scr_AddArrayKeys( lua_State *L );

// Script threads
static int Lua_Scr_ExecEntThread( lua_State *L );
static int Lua_Scr_ExecThread( lua_State *L );
static int Lua_Scr_FreeThread( lua_State *L );

// Get functions
static int Lua_Scr_GetNumParam( lua_State *L );
static int Lua_Scr_GetInt( lua_State *L );
static int Lua_Scr_GetFloat( lua_State *L );
static int Lua_Scr_GetString( lua_State *L );
static int Lua_Scr_GetEntity( lua_State *L );
static int Lua_Scr_GetType( lua_State *L );
static int Lua_Scr_GetVector( lua_State *L );
static int Lua_Cmd_Argv( lua_State *L );
static int Lua_Cmd_Argc( lua_State *L );

// Utility
static int Lua_Printf( lua_State *L );
static int Lua_DPrintf( lua_State *L );
static int Lua_GetPluginVersion( lua_State *L );
static int Lua_GetMilliseconds( lua_State *L );
static int Lua_Scr_Error( lua_State *L );
static int Lua_Scr_ParamError( lua_State *L );
static int Lua_Scr_ObjectError( lua_State *L );
static int Lua_Error( lua_State *L );



void *aligned_malloc( int size, int ALIGN );
char *AllocStub( char *funcName );
DWORD SetCall(DWORD addr, void* destination);

#endif // MAIN_H