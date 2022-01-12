#include "main.h"
#include "functions.h"
#include "http.h"
#include "pmysql.h"

lua_State *LuaVM = NULL;
char *AllocMem = NULL;
int definedFunctions = 0;

cvar_t *cvar_enableHttp;
cvar_t *cvar_enableMysql;

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
	else
	{
		Plugin_Printf( "****************** Lua Error: ******************\n\n%s\n", lua_tostring( LuaVM, -1 ) );	
		Plugin_Printf( "\n************************************************\n" );
	}

	lua_settop( LuaVM, 0 );
}

void Global_LuaHandler_Method( char *funcName, scr_entref_t entref )
{
	gentity_t *gentity = Plugin_GetGentityForEntityNum( entref );

	lua_getglobal( LuaVM, funcName );

	lua_pushlightuserdata( LuaVM, gentity );
	
	Plugin_Lua_pcall( LuaVM, 1, LUA_MULTRET );
	
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

	cvar_enableHttp = Plugin_Cvar_RegisterBool( "lua_enable_http", qfalse, CVAR_INIT, "Enable HTTP functionality of plugin" );
	cvar_enableMysql = Plugin_Cvar_RegisterBool( "lua_enable_mysql", qtrue, CVAR_INIT, "Enable MySQL functionality of plugin" );
	
	luaL_openlibs( LuaVM );
	
	registerFunctionsToLua();

	if( Plugin_Cvar_GetBoolean( cvar_enableHttp ) )
	{
		httpInit();
	}

	if( Plugin_Cvar_GetBoolean( cvar_enableMysql ) )
	{
		mysqlInit();
	}
	
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

int Lua_TraceBack( lua_State* L )
{
	Plugin_Printf( "****************** Lua Error: ******************\n\n%s\n", lua_tostring( L, -1 ) );
	luaL_traceback( L, L, NULL, 1 );
	
	Plugin_Printf( "%s\n\n************************************************\n", lua_tostring( L, -1 ) );
	
	return 0;
}

int Plugin_Lua_pcall( lua_State* L, int nargs, int nret )
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

char *AllocMethodStub( char *funcName )
{
	char *mem = AllocMem;
	mem += STUB_SIZE * definedFunctions;
	definedFunctions++;
	
	char *callback = mem;

	// [esp+4] - scr_entref_t param
	*(char*)mem = 0x8b; // mov eax, [esp+4]
	mem += sizeof( char );
	*(char*)mem = 0x44; 
	mem += sizeof( char );
	*(char*)mem = 0x24; 
	mem += sizeof( char );
	*(char*)mem = 0x04; 
	mem += sizeof( char );

	*(char*)mem = 0x50; // push eax
	mem += sizeof( char );

	*(char*)mem = 0x68; // Push dword
	mem += sizeof( char );
	*(int32_t*)mem = (int32_t)funcName;
	mem += sizeof( int32_t );

	*(char*)mem = 0xe8; // call
	mem += sizeof( char );
	*(int32_t*)mem = 0; // <- later function pointer
	mem += sizeof( int32_t );

	*(char*)mem = 0x83; // add esp, 8
	mem += sizeof( char );
	*(char*)mem = 0xc4;
	mem += sizeof( char );
	*(char*)mem = 0x08;
	mem += sizeof( char );

	*(char*)mem = 0xc3; // ret
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

PCL void OnPlayerAddBan(baninfo_t* baninfo)
{
	lua_getglobal( LuaVM, "OnPlayerAddBan" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		char pid[128];
		char sid[128];
		char aid[128];
		Plugin_SteamIDToString( baninfo->playerid, pid, sizeof( pid ) );
		Plugin_SteamIDToString( baninfo->steamid, sid, sizeof( sid ) );
		Plugin_SteamIDToString( baninfo->adminsteamid, aid, sizeof( aid ) );
		
		int perm = 0;
		if( baninfo->duration == 0 )
			perm = 1;
		
		lua_pushstring( LuaVM, pid );
		lua_pushstring( LuaVM, sid );
		lua_pushstring( LuaVM, aid );
		lua_pushinteger( LuaVM, perm );
		
		Plugin_Lua_pcall( LuaVM, 4, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnPlayerDC(client_t* client, const char* reason)
{
	lua_getglobal( LuaVM, "OnPlayerDC" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		char pid[128];
		char sid[128];
		Plugin_SteamIDToString( client->playerid, pid, sizeof( pid ) );
		Plugin_SteamIDToString( client->steamid, sid, sizeof( sid ) );
		
		lua_pushinteger( LuaVM, Plugin_GetClientNumForClient( client ) );
		lua_pushstring( LuaVM, pid );
		lua_pushstring( LuaVM, sid );
		
		Plugin_Lua_pcall( LuaVM, 3, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnFrame()
{
	if( Plugin_Cvar_GetBoolean( cvar_enableHttp ) )
	{
		Lua_HTTP_updateRequests();
	}
	if( Plugin_Cvar_GetBoolean( cvar_enableMysql ) )
	{
		Lua_Mysql_Update();
	}
	
	lua_getglobal( LuaVM, "OnFrame" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnPlayerGotAuthInfo(netadr_t* from, uint64_t* playerid, uint64_t *steamid, char *rejectmsg, qboolean *returnNow, client_t* cl)
{
	lua_getglobal( LuaVM, "OnPlayerGotAuthInfo" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		char pid[128];
		char sid[128];
		Plugin_SteamIDToString( cl->playerid, pid, sizeof( pid ) );
		Plugin_SteamIDToString( cl->steamid, sid, sizeof( sid ) );
		
		lua_pushinteger( LuaVM, Plugin_GetClientNumForClient( cl ) );
		lua_pushstring( LuaVM, pid );
		lua_pushstring( LuaVM, sid );
		lua_pushstring( LuaVM, rejectmsg );
		
		Plugin_Lua_pcall( LuaVM, 4, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnSpawnServer()
{
	lua_getglobal( LuaVM, "OnSpawnServer" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnPostFastRestart()
{
	lua_getglobal( LuaVM, "OnPostFastRestart" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnExitLevel()
{
	lua_getglobal( LuaVM, "OnExitLevel" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		Plugin_Lua_pcall( LuaVM, 0, LUA_MULTRET );	
	}
	
	lua_settop( LuaVM, 0 );
}

PCL void OnMessageSent(char* message, int slot, qboolean *show, int mode)
{
	lua_getglobal( LuaVM, "OnMessageSent" );
	
	if( lua_isfunction( LuaVM, -1 ) )
	{
		lua_pushstring( LuaVM, message );
		lua_pushinteger( LuaVM, slot );
		lua_pushboolean( LuaVM, (bool)show );
		lua_pushinteger( LuaVM, mode );
		Plugin_Lua_pcall( LuaVM, 4, LUA_MULTRET );	

		int n = lua_gettop( LuaVM );
	
		if( n == 1 )
		{
			*show = (qboolean)lua_toboolean( LuaVM, 1 );
		}
	}
	
	lua_settop( LuaVM, 0 );
}