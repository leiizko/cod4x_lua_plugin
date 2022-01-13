#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iconv.h>
#include <errno.h>

#define MAX_CD 3

void registerFunctionsToLua();

// Register functions
int Lua_Cmd_AddCommand( lua_State *L );
int Lua_ScrAddFunction( lua_State *L );
int Lua_ScrAddMethod( lua_State *L );

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
int Lua_Scr_AddArrayStringIndexed( lua_State *L );

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
int Lua_Cmd_Args( lua_State *L );
int Lua_Scr_GetFunc( lua_State *L );
//int Lua_Scr_GetFunctionHandle( lua_State *L );
int Lua_Cmd_GetInvokerSlot( lua_State *L );

// Utility
int Lua_Printf( lua_State *L );
int Lua_DPrintf( lua_State *L );
int Lua_GetPluginVersion( lua_State *L );
int Lua_GetMilliseconds( lua_State *L );
int Lua_Scr_Error( lua_State *L );
int Lua_Scr_ParamError( lua_State *L );
int Lua_Scr_ObjectError( lua_State *L );
int Lua_Error( lua_State *L );
int Lua_GetGentityForClientNum( lua_State *L );
int Lua_GetClientNumForGentity( lua_State *L );
int Lua_GetPlayerName( lua_State *L );
int Lua_DropClient( lua_State *L );
int Lua_BanClient( lua_State *L );
int Lua_GetClientScoreboard( lua_State *L );
int Lua_Scr_AllocString( lua_State *L );
int Lua_SV_SetConfigstring( lua_State *L );
int Lua_SV_GetConfigstring( lua_State *L );

// Cvars
int Lua_Cvar_RegisterString( lua_State *L );
int Lua_Cvar_RegisterBool( lua_State *L );
int Lua_Cvar_RegisterInt( lua_State *L );
int Lua_Cvar_RegisterFloat( lua_State *L );
int Lua_Cvar_SetString( lua_State *L );
int Lua_Cvar_SetBool( lua_State *L );
int Lua_Cvar_SetInt( lua_State *L );
int Lua_Cvar_SetFloat( lua_State *L );
int Lua_Cvar_GetString( lua_State *L );
int Lua_Cvar_GetBool( lua_State *L );
int Lua_Cvar_GetInt( lua_State *L );
int Lua_Cvar_GetFloat( lua_State *L );
int Lua_VariableStringBuffer( lua_State *L );
int Lua_Cvar_VariableValue( lua_State *L );
int Lua_Cvar_VariableIntegerValue( lua_State *L );
int Lua_Cvar_VariableBooleanValue( lua_State *L );
int Lua_Cvar_Set( lua_State *L );

// Notifies
int Lua_Scr_NotifyLevel( lua_State *L );
int Lua_Scr_Notify( lua_State *L );

// iconv
int Lua_iconv_open( lua_State *L );
int Lua_iconv_close( lua_State *L );
int Lua_iconv( lua_State *L );

#endif // FUNCTIONS_H