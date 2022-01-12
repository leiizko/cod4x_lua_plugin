#include "main.h"
#include "http.h"
#include "qcommon.h"

lua_httpReq openRequests[ LUA_HTTP_MAXOPENREQUESTS ];

void httpInit()
{
	lua_register( LuaVM, "Plugin_HTTP_makeRequest", Lua_HTTP_makeRequest );
}

int Lua_HTTP_makeRequest( lua_State *L )
{
	int n = lua_gettop( L );
	
	if( n < 3 )
	{
		luaL_error( L, "Plugin_HTTP_makeRequest: Function requires 4 parameters!" );
		return 1;
	}
	
	if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_HTTP_makeRequest: parameter 1 must be a string!" );
		return 1;
	}
	char *url = (char *)lua_tostring( L, 1 );
	
	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_HTTP_makeRequest: parameter 2 must be a string!" );
		return 1;
	}
	char *data = (char *)lua_tostring( L, 2 );
	
	if( !lua_isstring( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_HTTP_makeRequest: parameter 3 must be a string!" );
		return 1;
	}
	char *callback = (char *)lua_tostring( L, 3 );
	char *method = "POST";
	
	if( n == 4 )
	{
		if( !lua_isstring( L, 4 ) ) 
		{
			luaL_error( L, "Plugin_HTTP_makeRequest: parameter 4 must be a string!" );
			return 1;
		}
		method = (char *)lua_tostring( L, 4 );
	}
	
	lua_httpReq* r = NULL;
	for( int i = 0; i < LUA_HTTP_MAXOPENREQUESTS; ++i )
	{
		if( openRequests[ i ].request == NULL )
		{
			r = &openRequests[ i ];
			break;
		}
	}
	
	if( r == NULL )
	{
		Plugin_DPrintf( "Lua HTTP: max open requests reached!\n" );
		lua_pushinteger( L, 0 );
		return 1;
	}
	
	r->callback = Q_Strcpy( callback );
	if( r->callback == NULL )
	{
		lua_pushinteger( L, 0 );
		return 1;
	}

	if( !Q_stricmp( method, "POST" ) )
	{
		r->request = Plugin_HTTP_MakeHttpRequest( url, method, (byte *)data, strlen(data), "Content-Type: application/json\r\n" );
	}
	else
	{
		r->request = Plugin_HTTP_MakeHttpRequest( url, method, NULL, 0, NULL );
	}
	
	if( r->request == NULL )
	{
		Plugin_DPrintf( "Lua HTTP: Could not open new http request!\n" );
		free( r->callback );
		lua_pushinteger( L, 0 );
		return 1;
	}
	
	lua_pushinteger( L, 1 );
	return 1;
}

void Lua_HTTP_updateRequests()
{
	int i = 0;
	lua_httpReq* r = &openRequests[ i ];
	
	while( r->request != NULL )
	{
		int errCode = Plugin_HTTP_SendReceiveData( r->request );
		
		if( errCode == 1 || errCode == -1 )
		{
			byte* data = r->request->recvmsg.data + r->request->headerLength;
			
			lua_getglobal( LuaVM, r->callback );
			
			if( errCode == 1 )
			{
				lua_pushstring( LuaVM, (char *)data );
			}
			else
			{
				lua_pushnil( LuaVM );
			}
			Plugin_Lua_pcall( LuaVM, 1, LUA_MULTRET );
			
			lua_settop( LuaVM, 0 );
			
			Plugin_HTTP_FreeObj( r->request );
			r->request = NULL;

			free( r->callback );
			r->callback = NULL;
			
			popRequest( i );
			r = &openRequests[ i ];
			
			continue;
		}
		
		i++;
		if( i == LUA_HTTP_MAXOPENREQUESTS )
			break;

		r = &openRequests[ i ];
	}
}

void popRequest( int index )
{
	for( int i = index; i < LUA_HTTP_MAXOPENREQUESTS; ++i )
	{
		if( i + 1 >= LUA_HTTP_MAXOPENREQUESTS || openRequests[ i + 1 ].request == NULL )
		{
			openRequests[ i ].request = NULL;
			openRequests[ i ].callback = NULL;
			break;
		}
		
		openRequests[ i ] = openRequests[ i + 1 ];
	}
}