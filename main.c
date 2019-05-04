#include "main.h"
#include <math.h>

void Sv_LoadLuaScript()
{
	if( Plugin_Cmd_Argc() != 2 )
	{
		Plugin_Printf( "Error: lua_loadscript takes exactly 1 argument. Usage: lua_loadscript <script name> \nexample: lua_loadscript test.lua\n" );
		return;
	}
	
	char *scriptPath = Plugin_Cmd_Argv( 1 );
	
	if( !luaL_loadfile(LuaVM, scriptPath) )
	{
		if( !Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET ) )
		{
			Plugin_Printf( "lua_loadscript: Successfully started lua script %s\n", scriptPath );
			return;
		}
	}

	lua_settop( LuaVM, 0 );
}

void Global_LuaHandler( char *funcName )
{
	lua_getglobal( LuaVM, funcName );
	
	Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET );
	
	lua_settop( LuaVM, 0 );
}

void Sv_LuaDebug()
{
	Plugin_Printf( "KBytes used: %i\n", lua_gc( LuaVM, LUA_GCCOUNT, 0 ) );
	Plugin_Printf( "Elements on stack: %i\n", lua_gettop( LuaVM ) );
}

void registerFunctionsToLua()
{
	// Register functions
	lua_register( LuaVM, "Plugin_AddCommand", Lua_Cmd_AddCommand );
	lua_register( LuaVM, "Plugin_ScrAddFunction", Lua_ScrAddFunction );
	
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
	lua_register( LuaVM, "Plugin_Scr_AddArrayKeys", Lua_Scr_AddArrayKeys );
	
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
	
	// Utility
	lua_register( LuaVM, "Plugin_Printf", Lua_Printf );
	lua_register( LuaVM, "Plugin_DPrintf", Lua_DPrintf );
	lua_register( LuaVM, "Plugin_GetVersion", Lua_GetPluginVersion );
	lua_register( LuaVM, "Plugin_Milliseconds", Lua_GetMilliseconds );
	lua_register( LuaVM, "Plugin_Scr_Error", Lua_Scr_Error );
	lua_register( LuaVM, "Plugin_Scr_ParamError", Lua_Scr_ParamError );
	lua_register( LuaVM, "Plugin_Scr_ObjectError", Lua_Scr_ObjectError );
	lua_register( LuaVM, "Plugin_Error", Lua_Error );
}

PCL int OnInit()
{
	LuaVM = luaL_newstate();
	if( !LuaVM )
	{
		Plugin_Error( 2, "Lua Plugin: Failled getting LuaVM!\n" );
		return -1;
	}
	
	AllocMem = aligned_malloc( MAX_FUNCTIONS * STUB_SIZE, ALIGNMENT );
	
#ifdef _WIN32
	DWORD old;
	VirtualProtect( AllocMem, sizeof( AllocMem ), PAGE_EXECUTE_READWRITE, &old );
#else
	mprotect( AllocMem, sizeof( AllocMem ), PROT_EXEC | PROT_WRITE | PROT_READ );
#endif
	
	luaL_openlibs( LuaVM );
	
	registerFunctionsToLua();
	
	Plugin_AddCommand( "lua_loadscript", Sv_LoadLuaScript, 0 );
	Plugin_AddCommand( "lua_debug", Sv_LuaDebug, 0 );
	
    return 0;
}

PCL void OnInfoRequest( pluginInfo_t *info )
{
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

	info->pluginVersion.major = PLUGIN_VERSION_MAJOR;
	info->pluginVersion.minor = PLUGIN_VERSION_MINOR;	
	strncpy(info->fullName, "Lua plugin", sizeof(info->fullName));
	strncpy(info->shortDescription, "Implements Lua based plugins", sizeof(info->shortDescription));
	strncpy(info->longDescription, "Adds support for Lua based plugins, most suitable for adding script functions that are too expensive to run in GSC.", sizeof(info->longDescription));
}

static int Lua_Cmd_AddCommand( lua_State *L )
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
	
	if (!lua_isstring( L, 2 ) ) 
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

static int Lua_ScrAddFunction( lua_State *L )
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

static int Lua_Scr_AddEntity( lua_State *L )
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


static int Lua_Scr_AddInt( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Scr_AddInt: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Scr_AddInt: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	Plugin_Scr_AddInt( i );
	
	return 0;
}

static int Lua_Scr_AddFloat( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Scr_AddFloat: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Scr_AddFloat: Argument must be a float!\n" );
		return 1;
	}
	
	float i = (float)lua_tonumber( L, 1 );
	
	Plugin_Scr_AddFloat( i );
	
	return 0;
}

static int Lua_Scr_AddBool( lua_State *L )
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
	
	qboolean add = lua_toboolean( L, 1 );
	
	Plugin_Scr_AddBool( add );
	
	return 0;
}

static int Lua_Scr_AddString( lua_State *L )
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

static int Lua_Scr_AddUndefined( lua_State *L )
{
	Plugin_Scr_AddUndefined();

	return 0;
}

static int Lua_Scr_AddVector( lua_State *L )
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

static int Lua_Scr_AddArray( lua_State *L )
{
	Plugin_Scr_AddArray();

	return 0;
}

static int Lua_Scr_MakeArray( lua_State *L )
{
	Plugin_Scr_MakeArray();

	return 0;
}

static int Lua_Scr_AddArrayKeys( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Scr_AddArrayKeys: takes exactly one argument!\n" );
		return 1;
	}
	
	if (!lua_isnumber( L, 1 )) 
	{
		luaL_error( L, "Plugin_Scr_AddArrayKeys: Argument must be an integer!\n" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	Plugin_Scr_AddArrayKeys( i );
	
	return 0;
}

static int Lua_Scr_ExecEntThread( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n != 3 )
	{
		luaL_error( L, "Lua_Scr_ExecEntThread: takes three arguments!\n" );
		return 1;
	}
	
	if ( !lua_islightuserdata( L, 1 ) ) 
	{
		luaL_error( L, "Lua_Scr_ExecEntThread: Argument 1 must be an gentity_t!\n" );
		return 1;
	}
	
	gentity_t* ent = (gentity_t*)lua_touserdata( L, 1 );
	
	if ( !lua_isnumber( L, 2 ) ) 
	{
		luaL_error( L, "Lua_Scr_ExecEntThread: Argument 2 must be an integer!\n" );
		return 1;
	}
	
	int callbackHook = lua_tointeger( L, 2 );
	
	if ( !lua_isnumber( L, 3 ) ) 
	{
		luaL_error( L, "Lua_Scr_ExecEntThread: Argument 3 must be an integer!\n" );
		return 1;
	}
	
	int numArgs = (unsigned int)lua_tointeger( L, 3 );
	
	int result = (int)Plugin_Scr_ExecEntThread( ent, callbackHook, numArgs );
	
	lua_pushinteger( L, result );
	
	return 1;
}

static int Lua_Scr_ExecThread( lua_State *L )
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

static int Lua_Scr_FreeThread( lua_State *L )
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

static int Lua_Scr_GetNumParam( lua_State *L )
{
	int result = Plugin_Scr_GetNumParam();
	
	lua_pushinteger( L, result );
	
	return 1;
}

static int Lua_Scr_GetFloat( lua_State *L )
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

static int Lua_Scr_GetVector( lua_State *L )
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

static int Lua_Cmd_Argc( lua_State *L )
{
	int c = Plugin_Cmd_Argc();
	
	lua_pushinteger( L, c );
	
	return 1;
}

static int Lua_Cmd_Argv( lua_State *L )
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

static int Lua_Scr_GetType( lua_State *L )
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

static int Lua_Scr_GetInt( lua_State *L )
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

static int Lua_Scr_GetString( lua_State *L )
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

static int Lua_Scr_GetEntity( lua_State *L )
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

static int Lua_Printf( lua_State *L )
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

static int Lua_DPrintf( lua_State *L )
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

static int Lua_GetPluginVersion( lua_State *L )
{
	double version = PLUGIN_VERSION_MAJOR + ( PLUGIN_VERSION_MINOR * 0.1 );
	
	lua_pushnumber( L, version );
	
	return 1;
}

static int Lua_GetMilliseconds( lua_State *L )
{
	int msec = Plugin_Milliseconds();
	
	lua_pushinteger( L, msec );
	
	return 1;
}

static int Lua_Error( lua_State *L )
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

static int Lua_Scr_ObjectError( lua_State *L )
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

static int Lua_Scr_Error( lua_State *L )
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

static int Lua_Scr_ParamError( lua_State *L )
{
	int n = lua_gettop( L );
	if( n != 2 )
	{
		luaL_error( L, "Plugin_Scr_ParamError: Function takes two parameters!" );
		return 1;
	}
	
	if( !lua_isnumber( L, 1 ) )
	{
		luaL_error( L, "Plugin_Scr_Error: parameter 1 must be an int!" );
		return 1;
	}
	
	int i = lua_tointeger( L, 1 );
	
	if ( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_Error: parameter 2 must be a string!" );
		return 1;
	}
	
	const char *string = (const char *)lua_tostring( L, 2 );

	Plugin_Scr_ParamError( i, string );
	
	return 0;
}




static int Lua_TraceBack( lua_State* L )
{
	Plugin_Printf( "****************** Lua Error: ******************\n\n%s\n", lua_tostring( L, -1 ) );
	luaL_traceback( L, L, NULL, 1 );
	
	Plugin_Printf( "%s\n\n************************************************\n", lua_tostring( L, -1 ) );
	
	return 0;
}

static int Plugin_Lua_pcall( lua_State* L, int nargs, int nret )
{
	int hpos = lua_gettop( L ) - nargs;
	 
	lua_pushcfunction( L, Lua_TraceBack );
	
	lua_insert( L, hpos );
	
	int ret = lua_pcall( L, nargs, nret, hpos );
	
	lua_remove( L, hpos );
	
	return ret;
}

char *AllocStub( char *funcName )
{
	char *mem = AllocMem;
	mem += STUB_SIZE * definedFunctions;
	definedFunctions++;
	
	char *callback = mem;
	
	*(char*)mem = 0x68;
	mem += sizeof( char );
	*(int32_t*)mem = (int32_t)funcName;
	mem += sizeof( int32_t );
	*(char*)mem = 0xe8;
	mem += sizeof( char );
	*(int32_t*)mem = 0;
	mem += sizeof( int32_t );
	*(char*)mem = 0x83;
	mem += sizeof( char );
	*(char*)mem = 0xc4;
	mem += sizeof( char );
	*(char*)mem = 0x04;
	mem += sizeof( char );
	*(char*)mem = 0xc3;
	mem += sizeof( char );
	
	return callback;
}

DWORD SetCall(DWORD addr, void* destination)
{

	DWORD callwidth;
	DWORD restore;
	byte* baddr = (byte*)addr;

	callwidth = (DWORD)( destination - (void*)baddr - 5);
	*baddr = 0xe8;
	baddr++;

	restore = *(DWORD*)baddr;
	*(DWORD*)baddr = callwidth;

	return restore;
}

void *aligned_malloc( int size, int ALIGN )
{
    void *mem = malloc(size + (ALIGN - 1));
    
    void *ptr = (void**)((uintptr_t)(mem + (ALIGN - 1)) & ~(ALIGN - 1));

    return ptr;
}