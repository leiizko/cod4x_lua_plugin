#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef EICONV
	#include <iconv.h>
	#include <errno.h>
#endif // EICONV

void registerFunctionsToLua();

// Register functions
int Lua_Cmd_AddCommand( lua_State *L );
int Lua_ScrAddFunction( lua_State *L );

// Add functions
int Lua_Scr_AddEntity( lua_State *L );
int Lua_Scr_AddInt( lua_State *L );
int Lua_Scr_AddFloat( lua_State *L );
int Lua_Scr_AddBool( lua_State *L );
int Lua_Scr_AddString( lua_State *L );
int Lua_Scr_AddUndefined( lua_State *L );
int Lua_Scr_AddVector( lua_State *L );
int Lua_Scr_AddArray( lua_State *L );
int Lua_Scr_MakeArray( lua_State *L );
int Lua_Scr_AddArrayKeys( lua_State *L );

// Script threads
int Lua_Scr_ExecEntThread( lua_State *L );
int Lua_Scr_ExecThread( lua_State *L );
int Lua_Scr_FreeThread( lua_State *L );

// Get functions
int Lua_Scr_GetNumParam( lua_State *L );
int Lua_Scr_GetInt( lua_State *L );
int Lua_Scr_GetFloat( lua_State *L );
int Lua_Scr_GetString( lua_State *L );
int Lua_Scr_GetEntity( lua_State *L );
int Lua_Scr_GetType( lua_State *L );
int Lua_Scr_GetVector( lua_State *L );
int Lua_Cmd_Argv( lua_State *L );
int Lua_Cmd_Argc( lua_State *L );

// Utility
int Lua_Printf( lua_State *L );
int Lua_DPrintf( lua_State *L );
int Lua_GetPluginVersion( lua_State *L );
int Lua_GetMilliseconds( lua_State *L );
int Lua_Scr_Error( lua_State *L );
int Lua_Scr_ParamError( lua_State *L );
int Lua_Scr_ObjectError( lua_State *L );
int Lua_Error( lua_State *L );

// iconv
#ifdef EICONV
int Lua_iconv_open( lua_State *L );
int Lua_iconv_close( lua_State *L );
int Lua_iconv( lua_State *L );
#endif // EICONV

#endif // FUNCTIONS_H