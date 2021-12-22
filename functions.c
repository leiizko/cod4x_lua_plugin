#include "main.h"
#include "functions.h"

void registerFunctionsToLua()
{
	// Register functions
	lua_register( LuaVM, "Plugin_AddCommand", Lua_Cmd_AddCommand );
	lua_register( LuaVM, "Plugin_ScrAddFunction", Lua_ScrAddFunction );
	lua_register( LuaVM, "Plugin_ScrAddMethod", Lua_ScrAddMethod );
	
	// Add functions
	lua_register( LuaVM, "Plugin_Scr_AddEntity", Lua_Scr_AddEntity );
	lua_register( LuaVM, "Plugin_Scr_AddInt", Lua_Scr_AddInt );
	lua_register( LuaVM, "Plugin_Scr_AddFloat", Lua_Scr_AddFloat );
	lua_register( LuaVM, "Plugin_Scr_AddBool", Lua_Scr_AddBool );
	lua_register( LuaVM, "Plugin_Scr_AddString", Lua_Scr_AddString );
	lua_register( LuaVM, "Plugin_Scr_AddUndefined", Lua_Scr_AddUndefined );
	lua_register( LuaVM, "Plugin_Scr_AddVector", Lua_Scr_AddVector );
	lua_register( LuaVM, "Plugin_Scr_AddArray", Lua_Scr_AddArray );
	lua_register( LuaVM, "Plugin_Scr_MakeArray", Lua_Scr_MakeArray );
	lua_register( LuaVM, "Plugin_Scr_AddArrayStringIndexed", Lua_Scr_AddArrayStringIndexed );
	
	// Script threads
	lua_register( LuaVM, "Plugin_Scr_ExecEntThread", Lua_Scr_ExecEntThread );
	lua_register( LuaVM, "Plugin_Scr_ExecThread", Lua_Scr_ExecThread );
	lua_register( LuaVM, "Plugin_Scr_FreeThread", Lua_Scr_FreeThread );

	// Get functions
	lua_register( LuaVM, "Plugin_Scr_GetNumParam", Lua_Scr_GetNumParam );
	lua_register( LuaVM, "Plugin_Scr_GetInt", Lua_Scr_GetInt );
	lua_register( LuaVM, "Plugin_Scr_GetFloat", Lua_Scr_GetFloat );
	lua_register( LuaVM, "Plugin_Scr_GetString", Lua_Scr_GetString );
	lua_register( LuaVM, "Plugin_Scr_GetEntity", Lua_Scr_GetEntity );
	lua_register( LuaVM, "Plugin_Scr_GetType", Lua_Scr_GetType );
	lua_register( LuaVM, "Plugin_Scr_GetVector", Lua_Scr_GetVector );
	lua_register( LuaVM, "Plugin_Cmd_Argv", Lua_Cmd_Argv );
	lua_register( LuaVM, "Plugin_Cmd_Argc", Lua_Cmd_Argc );
	lua_register( LuaVM, "Plugin_Cmd_Args", Lua_Cmd_Args );
	lua_register( LuaVM, "Plugin_Scr_GetFunc", Lua_Scr_GetFunc );
//	lua_register( LuaVM, "Plugin_Scr_GetFunctionHandle", Lua_Scr_GetFunctionHandle );
	lua_register( LuaVM, "Plugin_Cmd_GetInvokerSlot", Lua_Cmd_GetInvokerSlot );

	
	// Utility
	lua_register( LuaVM, "Plugin_Printf", Lua_Printf );
	lua_register( LuaVM, "Plugin_DPrintf", Lua_DPrintf );
	lua_register( LuaVM, "Plugin_GetVersion", Lua_GetPluginVersion );
	lua_register( LuaVM, "Plugin_Milliseconds", Lua_GetMilliseconds );
	lua_register( LuaVM, "Plugin_Scr_Error", Lua_Scr_Error );
	lua_register( LuaVM, "Plugin_Scr_ParamError", Lua_Scr_ParamError );
	lua_register( LuaVM, "Plugin_Scr_ObjectError", Lua_Scr_ObjectError );
	lua_register( LuaVM, "Plugin_Error", Lua_Error );
	lua_register( LuaVM, "Plugin_GetGentityForClientNum", Lua_GetGentityForClientNum );
	lua_register( LuaVM, "Plugin_GetClientNumForGentity", Lua_GetClientNumForGentity );
	lua_register( LuaVM, "Plugin_GetPlayerName", Lua_GetPlayerName );
	lua_register( LuaVM, "Plugin_DropClient", Lua_DropClient );
	lua_register( LuaVM, "Plugin_BanClient", Lua_BanClient );
	lua_register( LuaVM, "Plugin_GetClientScoreboard", Lua_GetClientScoreboard );
	lua_register( LuaVM, "Plugin_Scr_AllocString", Lua_Scr_AllocString );
	lua_register( LuaVM, "Plugin_SV_SetConfigstring", Lua_SV_SetConfigstring );
	lua_register( LuaVM, "Plugin_SV_GetConfigstring", Lua_SV_GetConfigstring );

	// Cvars
	lua_register( LuaVM, "Plugin_Cvar_RegisterString", Lua_Cvar_RegisterString );
	lua_register( LuaVM, "Plugin_Cvar_RegisterBool", Lua_Cvar_RegisterBool );
	lua_register( LuaVM, "Plugin_Cvar_RegisterInt", Lua_Cvar_RegisterInt );
	lua_register( LuaVM, "Plugin_Cvar_RegisterFloat", Lua_Cvar_RegisterFloat );
	lua_register( LuaVM, "Plugin_Cvar_SetString", Lua_Cvar_SetString );
	lua_register( LuaVM, "Plugin_Cvar_SetBool", Lua_Cvar_SetBool );
	lua_register( LuaVM, "Plugin_Cvar_SetInt", Lua_Cvar_SetInt );
	lua_register( LuaVM, "Plugin_Cvar_SetFloat", Lua_Cvar_SetFloat );
	lua_register( LuaVM, "Plugin_Cvar_GetString", Lua_Cvar_GetString );
	lua_register( LuaVM, "Plugin_Cvar_GetBool", Lua_Cvar_GetBool );
	lua_register( LuaVM, "Plugin_Cvar_GetInt", Lua_Cvar_GetInt );
	lua_register( LuaVM, "Plugin_Cvar_GetFloat", Lua_Cvar_GetFloat );
	lua_register( LuaVM, "Plugin_Cvar_VariableStringBuffer", Lua_VariableStringBuffer );
	lua_register( LuaVM, "Plugin_Cvar_VariableValue", Lua_Cvar_VariableValue );
	lua_register( LuaVM, "Plugin_Cvar_VariableIntegerValue", Lua_Cvar_VariableIntegerValue );
	lua_register( LuaVM, "Plugin_Cvar_VariableBooleanValue", Lua_Cvar_VariableBooleanValue );
	lua_register( LuaVM, "Plugin_Cvar_Set", Lua_Cvar_Set );

	// Notifies
	lua_register( LuaVM, "Plugin_Scr_NotifyLevel", Lua_Scr_NotifyLevel );
	lua_register( LuaVM, "Plugin_Scr_Notify", Lua_Scr_Notify );
	
	// iconv
#ifdef EICONV
	lua_register( LuaVM, "Plugin_iconv_open", Lua_iconv_open );
	lua_register( LuaVM, "Plugin_iconv_close", Lua_iconv_close );
	lua_register( LuaVM, "Plugin_iconv", Lua_iconv );
#endif // EICONV
}

#ifdef EICONV

#define MAX_CD 3
iconv_t cd_g[ MAX_CD ];
int Lua_iconv( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_iconv: Function requires exactly 2 parameters!" );
		return 1;
	}
	
	if( !lua_isnumber ( L, 1 ) )
	{
		luaL_error( L, "Plugin_iconv: parameter 1 must be an integer!" );
		return 1;
	}
	
	int idx = lua_tointeger( L, 1 );
	
	if( idx < 0 || idx >= MAX_CD || cd_g[ idx ] == NULL )
	{
		luaL_error( L, "Plugin_iconv: parameter 1 is invalid!" );
		return 1;
	}

	if( !lua_isstring( L, 2 ) )
	{
		luaL_error( L, "Plugin_iconv: parameter 2 must be a string!" );
		return 1;
	}
	
	char *inbuf = (char *)lua_tostring( L, 2 );
	size_t inbytesleft = lua_objlen( L, 2 );
	char outbufa[ 1024 ];
	char *outbuf = outbufa;
	char *outbuf_start = outbufa;
	size_t outbytesleft = 1024;
	
	size_t ret = iconv( cd_g[ idx ], &inbuf, &inbytesleft, &outbuf, &outbytesleft );
	if( ret == ( size_t )( -1 ) )
	{
		if( errno == EILSEQ )
		{
			luaL_error( L, "Plugin_iconv: An invalid multibyte sequence is encountered in the input!" );
			return 1;
		}
		else if( errno == EINVAL )
		{
			luaL_error( L, "Plugin_iconv: An incomplete multibyte sequence is encountered in the input!" );
			return 1;
		}
		else if( errno == E2BIG )
		{
			luaL_error( L, "Plugin_iconv: The output buffer has no more room for the next converted character!" );
			return 1;
		}
		else
		{
			luaL_error( L, "Plugin_iconv: Unknown error!" );
			return 1;
		}
	}
	*outbuf = '\0';
	lua_pushstring( L, outbuf_start );
	return 1;
}

int Lua_iconv_close( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_iconv_close: Function requires exactly 1 parameter!" );
		return 1;
	}
	
	if( !lua_isnumber ( L, 1 ) )
	{
		luaL_error( L, "Plugin_iconv_close: parameter 1 must be an integer!" );
		return 1;
	}
	
	int idx = lua_tointeger( L, 1 );
	
	if( idx < 0 || idx >= MAX_CD || cd_g[ idx ] == NULL )
	{
		luaL_error( L, "Plugin_iconv_close: parameter 1 is invalid!" );
		return 1;
	}
	
	int status = iconv_close( cd_g[ idx ] );
	if( status == -1 )
	{
		luaL_error( L, "Plugin_iconv_close: Unknown error!" );
		return 1;
	}
	
	cd_g[ idx ] = NULL;
	lua_pushinteger( L, status );
	
	return 1;
}

int Lua_iconv_open( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_iconv_open: Function requires exactly 2 parameters!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) )
	{
		luaL_error( L, "Plugin_iconv_open: parameter 1 must be a string!" );
		return 1;
	}
	
	const char *toCode = (const char *)lua_tostring( L, 1 );
	
	if( !lua_isstring( L, 2 ) )
	{
		luaL_error( L, "Plugin_iconv_open: parameter 2 must be a string!" );
		return 1;
	}
	
	const char *fromCode = (const char *)lua_tostring( L, 2 );
	
	int idx = -1;
	for( int i = 0; i < MAX_CD; i++ )
	{
		if( cd_g[ i ] == NULL )
		{
			idx = i;
			break;
		}
	}
	if( idx < 0 )
	{
		luaL_error( L, "Plugin_iconv_open: No free conversion slots!" );
		return 1;
	}
	
	cd_g[ idx ]= iconv_open( toCode, fromCode );
	
	if( cd_g[ idx ] != ( iconv_t )( -1 ) )
	{
		lua_pushinteger( L, idx );
		return 1;
	}
	else
	{
		if( errno == EINVAL )
		{
			luaL_error( L, "Plugin_iconv_open: The conversion from fromcode to tocode is not supported!" );
			return 1;
		}
		else
		{
			luaL_error( L, "Plugin_iconv_open: Unknown error!" );
			return 1;
		}
	}
}
#endif // EICONV

int Lua_Cmd_AddCommand( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_AddCommand: Function requires exactly 2 parameters!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_AddCommand: parameter 1 must be a string!" );
		return 1;
	}
	char *funcName = (char *)lua_tostring( L, 1 );
	
	if (!lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_AddCommand: parameter 2 must be an integer!" );
		return 1;
	}
	int power = lua_tointeger( L, 2 );
	
	char *callback = AllocStub( funcName );

	SetCall( (DWORD)callback + 5, Global_LuaHandler );
	
	Plugin_AddCommand( funcName, (void *)callback, power );

	return 0;
}

int Lua_ScrAddFunction( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_ScrAddFunction: Function requires exactly 1 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_ScrAddFunction: parameter 1 must be a string!" );
		return 1;
	}
	char *funcName = (char *)lua_tostring( L, 1 );

	char *callback = AllocStub( funcName );

	SetCall( (DWORD)callback + 5, Global_LuaHandler );
	
	Plugin_ScrAddFunction( funcName, (void *)callback );

	return 0;
}

int Lua_ScrAddMethod( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_ScrAddMethod: Function requires exactly 1 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_ScrAddMethod: parameter 1 must be a string!" );
		return 1;
	}
	char *funcName = (char *)lua_tostring( L, 1 );

	char *callback = AllocMethodStub( funcName );

	SetCall( (DWORD)callback + 10, Global_LuaHandler_Method );
	
	Plugin_ScrAddMethod( funcName, (void *)callback );

	return 0;
}

int Lua_Scr_AddEntity( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddEntity: takes exactly one argument!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_AddEntity: Argument 1 must be an gentity_t!\n" );
		return 1;
	}
	
	gentity_t* ent = (gentity_t*)lua_touserdata( L, 1 );
	
	Plugin_Scr_AddEntity( ent );
	
	return 0;
}


int Lua_Scr_AddInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddInt: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_AddInt: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	Plugin_Scr_AddInt( i );
	
	return 0;
}

int Lua_Scr_AddFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddFloat: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_AddFloat: Argument must be a float!\n" );
		return 1;
	}
	
	float i = (float)lua_tonumber( L, 1 );
	
	Plugin_Scr_AddFloat( i );
	
	return 0;
}

int Lua_Scr_AddBool( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddBool: takes exactly one argument!\n" );
		return 1;
	}
	
	if( lua_isboolean( L, 1 ) )
	{
		luaL_error( L, "Plugin_Scr_AddBool: Argument must be boolean!\n" );
		return 1;
	}
	
	qboolean add = (qboolean)lua_toboolean( L, 1 );
	
	Plugin_Scr_AddBool( add );
	
	return 0;
}

int Lua_Scr_AddString( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddString: Function requires exactly 1 parameters!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_AddString: parameter 1 must be a string!" );
		return 1;
	}
	char *string = (char *)lua_tostring( L, 1 );

	Plugin_Scr_AddString( string );

	return 0;
}

int Lua_Scr_AddUndefined( lua_State *L )
{
	Plugin_Scr_AddUndefined();

	return 0;
}

int Lua_Scr_AddVector( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddVector: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_istable( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_AddVector: Argument must be a vec3!\n" );
		return 1;
	}
	
	vec3_t vec;
	
	for ( int i = 1; i <= 3; i++ )
	{
		lua_pushinteger( L, i );
		lua_gettable( L, 1 );
		
		if( lua_isnil( L, -1 ) )
		{
			luaL_error( L, "Plugin_Scr_AddVector: Argument must be a vec3!\n" );
			return 1;
		}
		
		if ( !lua_isnumber( L, -1 ) )
		{
			luaL_error( L, "Plugin_Scr_AddVector: vec3 must be a number!\n" );
			return 1;
		}
		
		vec[ i - 1 ] = (float)lua_tonumber( L, -1 );
		lua_pop( L, 1 );
	}
	
	Plugin_Scr_AddVector( vec );
	
	return 0;
}

int Lua_Scr_AddArray( lua_State *L )
{
	Plugin_Scr_AddArray();

	return 0;
}

int Lua_Scr_MakeArray( lua_State *L )
{
	Plugin_Scr_MakeArray();

	return 0;
}

int Lua_Scr_AddArrayStringIndexed( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddArrayStringIndexed: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_AddArrayStringIndexed: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	Plugin_Scr_AddArrayStringIndexed( i );
	
	return 0;
}

int Lua_Scr_ExecEntThread( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 3 )
	{
		luaL_error( L, "Plugin_Scr_ExecEntThread: takes three arguments!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ExecEntThread: Argument 1 must be an gentity_t!\n" );
		return 1;
	}
	
	gentity_t* ent = (gentity_t*)lua_touserdata( L, 1 );
	
	if ( !lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ExecEntThread: Argument 2 must be an integer!\n" );
		return 1;
	}
	
	int callbackHook = lua_tointeger( L, 2 );
	
	if ( !lua_isnumber( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ExecEntThread: Argument 3 must be an integer!\n" );
		return 1;
	}
	
	int numArgs = (unsigned int)lua_tointeger( L, 3 );
	
	int result = (int)Plugin_Scr_ExecEntThread( ent, callbackHook, numArgs );
	
	lua_pushinteger( L, result );
	
	return 1;
}

int Lua_Scr_ExecThread( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Scr_ExecThread: takes two arguments!\n" );
		return 1;
	}
	
	if ( !lua_isnumber( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ExecThread: Argument 1 must be an integer!\n" );
		return 1;
	}
	
	int callbackHook = lua_tointeger( L, 1 );
	
	if ( !lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ExecThread: Argument 2 must be an integer!\n" );
		return 1;
	}
	
	int numArgs = (unsigned int)lua_tointeger( L, 2 );
	
	int result = (int)Plugin_Scr_ExecThread( callbackHook, numArgs );
	
	lua_pushinteger( L, result );
	
	return 1;
}

int Lua_Scr_FreeThread( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_FreeThread: takes exactly one argument!\n" );
		return 1;
	}
	
	if ( !lua_isnumber( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_FreeThread: Argument 1 must be an integer!\n" );
		return 1;
	}
	
	short threadId = (short)lua_tointeger( L, 1 );
	
	Plugin_Scr_FreeThread( threadId );
	
	return 0;
}

int Lua_Scr_GetNumParam( lua_State *L )
{
	int result = Plugin_Scr_GetNumParam();
	
	lua_pushinteger( L, result );
	
	return 1;
}

int Lua_Scr_GetFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Scr_GetFloat: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Scr_GetFloat: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	float result = Plugin_Scr_GetFloat( i );
	
	lua_pushnumber( L, (double)result );
	
	return 1;
}

int Lua_Scr_GetVector( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetVector: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetVector: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	vec3_t vec;
	
	Plugin_Scr_GetVector( i, &vec );
	
	lua_newtable( L );
	for( int i = 0; i < 3; i++ )
	{
		lua_pushnumber( L, vec[ i ] );
		lua_rawseti( L, -2, i + 1 );
	}
	
	return 1;
}

int Lua_Cmd_Argc( lua_State *L )
{
	int c = Plugin_Cmd_Argc();
	
	lua_pushinteger( L, c );
	
	return 1;
}

int Lua_Cmd_Args( lua_State *L )
{
	char tmp[ 256 ];
	Plugin_Cmd_Args( tmp, sizeof( tmp ) );
	
	lua_pushstring( L, tmp );
	
	return 1;
}

int Lua_Cmd_Argv( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cmd_Argv: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Cmd_Argv: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	char *result = Plugin_Cmd_Argv( i );
	
	lua_pushstring( L, result );
	
	return 1;
}

int Lua_Scr_GetType( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetType: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetType: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	unsigned int result = Plugin_Scr_GetType( i );
	
	lua_pushinteger( L, result );
	
	return 1;
}

int Lua_Scr_GetInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetInt: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetInt: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	int result = Plugin_Scr_GetInt( i );
	
	lua_pushinteger( L, result );
	
	return 1;
}

int Lua_Scr_GetString( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetString: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetString: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	char *result = Plugin_Scr_GetString( i );
	
	lua_pushstring( L, result );
	
	return 1;
}

int Lua_Scr_GetEntity( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetEntity: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetEntity: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	gentity_t *result = Plugin_Scr_GetEntity( i );
	
	lua_pushlightuserdata( L, result );
	
	return 1;
}

int Lua_Scr_GetFunc( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_GetFunc: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_GetFunc: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	int result = Plugin_Scr_GetFunc( i );
	
	lua_pushinteger( L, result );
	
	return 1;
}

#if 0
// Works only in script runtime initialization
int Lua_Scr_GetFunctionHandle( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Scr_GetFunctionHandle: Function takes 2 parameters!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_GetFunctionHandle: parameter 1 must be a string!" );
		return 1;
	}
	const char *fileName = ( const char *)lua_tostring( L, 1 );

	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_GetFunctionHandle: parameter 2 must be a string!" );
		return 1;
	}
	const char *functionName = ( const char *)lua_tostring( L, 2 );

	int fh = Plugin_Scr_GetFunctionHandle( fileName, functionName );

	lua_pushinteger( L, fh );
	
	return 1;
}
#endif

int Lua_Cmd_GetInvokerSlot( lua_State *L )
{
	int invoker = Plugin_Cmd_GetInvokerSlot();

	lua_pushinteger( L, invoker );
	
	return 1;
}

int Lua_Printf( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Printf: Function takes exactly one parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Printf: parameter must be a string!" );
		return 1;
	}

	Plugin_Printf( (char *)lua_tostring( L, 1 ) );
	
	return 0;
}

int Lua_DPrintf( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_DPrintf: Function takes exactly one parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_DPrintf: parameter must be a string!" );
		return 1;
	}

	Plugin_DPrintf( (char *)lua_tostring( L, 1 ) );
	
	return 0;
}

int Lua_GetPluginVersion( lua_State *L )
{
	double version = PLUGIN_VERSION_MAJOR + ( PLUGIN_VERSION_MINOR * 0.1 );
	
	lua_pushnumber( L, version );
	
	return 1;
}

int Lua_GetMilliseconds( lua_State *L )
{
	int msec = Plugin_Milliseconds();
	
	lua_pushinteger( L, msec );
	
	return 1;
}

int Lua_Error( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Error: Function takes two parameters!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_Error: parameter 1 must be an int!" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	if ( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Error: parameter 2 must be a string!" );
		return 1;
	}
	
	const char *string = (const char *)lua_tostring( L, 2 );

	Plugin_Error( i, string );
	
	return 0;
}

int Lua_Scr_ObjectError( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_ObjectError: Function takes exactly one parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ObjectError: parameter must be a string!" );
		return 1;
	}
	
	const char *string = (const char *)lua_tostring( L, 1 );

	Plugin_Scr_ObjectError( string );
	
	return 0;
}

int Lua_Scr_Error( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_Error: Function takes exactly one parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_Error: parameter must be a string!" );
		return 1;
	}
	
	const char *string = (const char *)lua_tostring( L, 1 );

	Plugin_Scr_Error( string );
	
	return 0;
}

int Lua_Scr_ParamError( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Scr_ParamError: Function takes two parameters!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_Scr_ParamError: parameter 1 must be an int!" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	if ( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_ParamError: parameter 2 must be a string!" );
		return 1;
	}
	
	const char *string = (const char *)lua_tostring( L, 2 );

	Plugin_Scr_ParamError( i, string );
	
	return 0;
}

int Lua_GetGentityForClientNum( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_GetGentityForClientNum: Function takes exactly 1 parameter!" );
		return 1;
	}

	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_GetGentityForClientNum: parameter 1 must be an int!" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );

	client_t *cl = Plugin_GetClientForClientNum( i );
	if( cl == NULL )
	{
		lua_pushnil( L );
		Plugin_Printf( "Plugin_GetGentityForClientNum: invalid client num!\n" );
		return 1;
	}

	gentity_t *ent = cl->gentity;

	lua_pushlightuserdata( L, ent );

	return 1;
}

int Lua_GetClientNumForGentity( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_GetClientNumForGentity: takes exactly one argument!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_GetClientNumForGentity: Argument 1 must be an gentity_t!\n" );
		return 1;
	}
	
	gentity_t* ent = (gentity_t*)lua_touserdata( L, 1 );

	if( ent->client == NULL )
	{
		lua_pushnil( L );
		Plugin_Printf( "Plugin_GetClientNumForGentity: invalid client num!\n" );
		return 1;
	}
	
	int cnum = ent->client->sess.cs.clientIndex;

	lua_pushinteger( L, cnum );
	
	return 1;
}

int Lua_GetPlayerName( lua_State *L )
{
	int n = lua_gettop( L );

	if( n != 1 )
	{
		luaL_error( L, "Plugin_GetPlayerName: Function takes 1 parameter!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_GetPlayerName: parameter 1 must be an int!" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );

	char *name = Plugin_GetPlayerName( i );

	lua_pushstring( L, name );

	return 1;
}

int Lua_DropClient( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_DropClient: Function takes two parameters!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_DropClient: parameter 1 must be an int!" );
		return 1;
	}
	int cnum = lua_tointeger( L, 1 );
	
	if ( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_DropClient: parameter 2 must be a string!" );
		return 1;
	}
	const char *reason = (const char *)lua_tostring( L, 2 );

	Plugin_DropClient( cnum, reason );
	
	return 0;
}

int Lua_BanClient( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 4 )
	{
		luaL_error( L, "Plugin_BanClient: Function takes 4 parameters!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_BanClient: parameter 1 must be an int!" );
		return 1;
	}
	int cnum = lua_tointeger( L, 1 );

	if( !lua_isnumber( L, 2 ) )
	{
		luaL_error( L, "Plugin_BanClient: parameter 2 must be an int!" );
		return 1;
	}
	int time = lua_tointeger( L, 2 );

	if( !lua_isnumber( L, 3 ) )
	{
		luaL_error( L, "Plugin_BanClient: parameter 3 must be an int!" );
		return 1;
	}
	int iid = lua_tointeger( L, 3 );
	
	if ( !lua_isstring( L, 4 ) ) 
	{
		luaL_error( L, "Plugin_DropClient: parameter 4 must be a string!" );
		return 1;
	}
	char *reason = (char *)lua_tostring( L, 4 );

	Plugin_BanClient( cnum, time, iid, reason );
	
	return 0;
}

int Lua_GetClientScoreboard( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_GetClientScoreboard: Function takes 1 parameter!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_GetClientScoreboard: parameter 1 must be an int!" );
		return 1;
	}
	int cnum = lua_tointeger( L, 1 );

	clientScoreboard_t sb = Plugin_GetClientScoreboard( cnum );

	lua_newtable( L );
	lua_pushinteger( L, sb.kills );
	lua_setfield( L, -2, "kills" );
	lua_pushinteger( L, sb.assists );
	lua_setfield( L, -2, "assists" );
	lua_pushinteger( L, sb.deaths );
	lua_setfield( L, -2, "deaths" );
	lua_pushinteger( L, sb.score );
	lua_setfield( L, -2, "score" );
	
	return 1;
}

int Lua_Scr_AllocString( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AllocString: Function takes 1 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) )
	{
		luaL_error( L, "Plugin_GetClientScoreboard: parameter 1 must be a string!" );
		return 1;
	}
	const char *str = (const char*)lua_tostring( L, 1 );

	int i = Plugin_Scr_AllocString( str );

	lua_pushinteger( L, i );
	
	return 1;
}

int Lua_SV_SetConfigstring( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_SV_SetConfigstring: Function takes 2 parameters!" );
		return 1;
	}

	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_SV_SetConfigstring: parameter 1 must be an int!" );
		return 1;
	}	
	int idx = lua_tointeger( L, 1 );
	
	if( !lua_isstring( L, 2 ) )
	{
		luaL_error( L, "Plugin_SV_SetConfigstring: parameter 2 must be a string!" );
		return 1;
	}
	const char *str = (const char*)lua_tostring( L, 2 );

	Plugin_SV_SetConfigstring( idx, str );
	
	return 0;
}

int Lua_SV_GetConfigstring( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 1 )
	{
		luaL_error( L, "Plugin_SV_GetConfigstring: Function takes 1 parameter!" );
		return 1;
	}

	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_SV_GetConfigstring: parameter 1 must be an int!" );
		return 1;
	}	
	int idx = lua_tointeger( L, 1 );

	char tmp[ 1024 ];
	Plugin_SV_GetConfigstring( idx, tmp, sizeof( tmp ) );

	lua_pushstring( L, tmp );
	
	return 1;
}

int Lua_Cvar_RegisterString( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 4 )
	{
		luaL_error( L, "Plugin_Cvar_RegisterString: Function requires exactly 4 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterString: parameter 1 must be a string!" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterString: parameter 2 must be a string!" );
		return 1;
	}
	char *varValue = (char *)lua_tostring( L, 2 );

	if( !lua_isnumber( L, 3 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterString: parameter 3 must be an int!" );
		return 1;
	}	
	int flags = lua_tointeger( L, 3 );

	if( !lua_isstring( L, 4 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterString: parameter 4 must be a string!" );
		return 1;
	}
	char *varDesc = (char *)lua_tostring( L, 4 );

	CONVAR_T* cvar = Plugin_Cvar_RegisterString( varName, varValue, flags, varDesc );

	lua_pushlightuserdata( L, cvar );

	return 1;
}

int Lua_Cvar_RegisterBool( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 4 )
	{
		luaL_error( L, "Plugin_Cvar_RegisterBool: Function requires exactly 4 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterBool: parameter 1 must be a string!" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	if( lua_isboolean( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterBool: parameter 2 must be boolean!\n" );
		return 1;
	}
	qboolean varValue = (qboolean)lua_toboolean( L, 2 );

	if( !lua_isnumber( L, 3 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterBool: parameter 3 must be an int!" );
		return 1;
	}	
	int flags = lua_tointeger( L, 3 );

	if( !lua_isstring( L, 4 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterBool: parameter 4 must be a string!" );
		return 1;
	}
	char *varDesc = (char *)lua_tostring( L, 4 );

	CONVAR_T* cvar = Plugin_Cvar_RegisterBool( varName, varValue, flags, varDesc );

	lua_pushlightuserdata( L, cvar );

	return 1;
}

int Lua_Cvar_RegisterInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 6 )
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: Function requires exactly 6 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 1 must be a string!" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	if( !lua_isnumber( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 2 must be an int!" );
		return 1;
	}	
	int value = lua_tointeger( L, 2 );

	if( !lua_isnumber( L, 3 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 3 must be an int!" );
		return 1;
	}	
	int minvalue = lua_tointeger( L, 3 );

	if( !lua_isnumber( L, 4 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 4 must be an int!" );
		return 1;
	}	
	int maxvalue = lua_tointeger( L, 4 );

	if( !lua_isnumber( L, 5 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 5 must be an int!" );
		return 1;
	}	
	int flags = lua_tointeger( L, 5 );

	if( !lua_isstring( L, 6 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterInt: parameter 6 must be a string!" );
		return 1;
	}
	char *varDesc = (char *)lua_tostring( L, 6 );

	CONVAR_T* cvar = Plugin_Cvar_RegisterInt( varName, value, minvalue, maxvalue, flags, varDesc );

	lua_pushlightuserdata( L, cvar );

	return 1;
}

int Lua_Cvar_RegisterFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 6 )
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: Function requires exactly 6 parameter!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 1 must be a string!" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	if( !lua_isnumber( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 2 must be a float!" );
		return 1;
	}	
	float value = (float)lua_tonumber( L, 2 );

	if( !lua_isnumber( L, 3 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 3 must be a float!" );
		return 1;
	}	
	float minvalue = (float)lua_tonumber( L, 3 );

	if( !lua_isnumber( L, 4 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 4 must be a float!" );
		return 1;
	}	
	float maxvalue = (float)lua_tonumber( L, 4 );

	if( !lua_isnumber( L, 5 ) )
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 5 must be an int!" );
		return 1;
	}	
	int flags = lua_tointeger( L, 5 );

	if( !lua_isstring( L, 6 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_RegisterFloat: parameter 6 must be a string!" );
		return 1;
	}
	char *varDesc = (char *)lua_tostring( L, 6 );

	CONVAR_T* cvar = Plugin_Cvar_RegisterFloat( varName, value, minvalue, maxvalue, flags, varDesc );

	lua_pushlightuserdata( L, cvar );

	return 1;
}

int Lua_Cvar_SetString( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Cvar_SetString: takes 2 parameters!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_SetString: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_SetString: parameter 2 must be a string!\n" );
		return 1;
	}
	char *value = (char *)lua_tostring( L, 1 );

	Plugin_Cvar_SetString( cvar, value );

	return 0;
}

int Lua_Cvar_SetBool( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Cvar_SetBool: takes 2 parameters!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_SetBool: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	if( lua_isboolean( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_SetBool: parameter 2 must be boolean!\n" );
		return 1;
	}
	qboolean value = (qboolean)lua_toboolean( L, 2 );

	Plugin_Cvar_SetBool( cvar, value );

	return 0;
}

int Lua_Cvar_SetInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Cvar_SetInt: takes 2 parameters!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_SetInt: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	if( !lua_isnumber( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_SetInt: parameter 2 must be an int!\n" );
		return 1;
	}	
	int value = lua_tointeger( L, 2 );

	Plugin_Cvar_SetInt( cvar, value );

	return 0;
}

int Lua_Cvar_SetFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Cvar_SetFloat: takes 2 parameters!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_SetFloat: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	if( !lua_isnumber( L, 2 ) )
	{
		luaL_error( L, "Plugin_Cvar_SetFloat: parameter 2 must be a float!\n" );
		return 1;
	}	
	float value = (float)lua_tonumber( L, 2 );

	Plugin_Cvar_SetFloat( cvar, value );

	return 0;
}

int Lua_Cvar_GetString( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_GetFloat: takes 1 parameter!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_GetFloat: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	char tmp[ 1024 ];
	Plugin_Cvar_GetString( cvar, tmp, sizeof( tmp ) );

	lua_pushstring( L , tmp );

	return 1;
}

int Lua_Cvar_GetBool( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_GetBool: takes 1 parameter!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_GetBool: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	qboolean value = Plugin_Cvar_GetBoolean( cvar );

	lua_pushboolean( L, (bool)value );

	return 1;
}

int Lua_Cvar_GetInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_GetInt: takes 1 parameter!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_GetInt: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	int value = Plugin_Cvar_GetInteger( cvar );

	lua_pushinteger( L, value );

	return 1;
}

int Lua_Cvar_GetFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_GetFloat: takes 1 parameter!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_GetFloat: parameter 1 must be a CONVAR_T!\n" );
		return 1;
	}
	CONVAR_T* cvar = (CONVAR_T*)lua_touserdata( L, 1 );

	float value = Plugin_Cvar_GetValue( cvar );

	lua_pushnumber( L, value );

	return 1;
}

int Lua_VariableStringBuffer( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_VariableStringBuffer: takes 1 parameter!\n" );
		return 1;
	}

	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_VariableStringBuffer: parameter 1 must be a string!\n" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	char tmp[ 1024 ];
	Plugin_Cvar_VariableStringBuffer( varName, tmp, sizeof( tmp ) );

	lua_pushstring( L, tmp );

	return 1;
}

int Lua_Cvar_VariableValue( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_VariableValue: takes 1 parameter!\n" );
		return 1;
	}

	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_VariableValue: parameter 1 must be a string!\n" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	float value = Plugin_Cvar_VariableValue( varName );

	lua_pushnumber( L, value );

	return 1;
}

int Lua_Cvar_VariableIntegerValue( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_VariableIntegerValue: takes 1 parameter!\n" );
		return 1;
	}

	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_VariableIntegerValue: parameter 1 must be a string!\n" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	int value = Plugin_Cvar_VariableIntegerValue( varName );

	lua_pushnumber( L, value );

	return 1;
}

int Lua_Cvar_VariableBooleanValue( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Cvar_VariableBooleanValue: takes 1 parameter!\n" );
		return 1;
	}

	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_VariableBooleanValue: parameter 1 must be a string!\n" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	int value = Plugin_Cvar_VariableBooleanValue( varName );

	lua_pushboolean( L, (bool)value );

	return 1;
}

int Lua_Cvar_Set( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Cvar_Set: takes 2 parameters!\n" );
		return 1;
	}

	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_Set: parameter 1 must be a string!\n" );
		return 1;
	}
	char *varName = (char *)lua_tostring( L, 1 );

	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Cvar_Set: parameter 2 must be a string!\n" );
		return 1;
	}
	char *value = (char *)lua_tostring( L, 2 );

	Plugin_Cvar_Set( varName, value );

	return 0;
}

int Lua_Scr_NotifyLevel( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Scr_NotifyLevel: takes 2 parameters!\n" );
		return 1;
	}

	if( !lua_isnumber( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_NotifyLevel: parameter 1 must be an int of const string!\n" );
		return 1;
	}
	int constString = lua_tointeger( L, 1 );

	if( !lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_NotifyLevel: parameter 2 must be an int!\n" );
		return 1;
	}
	int numArgs = lua_tointeger( L, 2 );

	Plugin_Scr_NotifyLevel( constString, numArgs );

	return 0;
}

int Lua_Scr_Notify( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 3 )
	{
		luaL_error( L, "Plugin_Scr_Notify: takes 3 parameters!\n" );
		return 1;
	}

	if( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Scr_Notify: parameter 1 must be a gentity_t!\n" );
		return 1;
	}
	gentity_t *ent = (gentity_t*)lua_touserdata( L, 1 );

	if( !lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_Notify: parameter 2 must be an int of const string!\n" );
		return 1;
	}
	int constString = lua_tointeger( L, 2 );

	if( !lua_isnumber( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_Scr_Notify: parameter 3 must be an int!\n" );
		return 1;
	}
	int numArgs = lua_tointeger( L, 3 );

	Plugin_Scr_Notify( ent, constString, numArgs );

	return 0;
}