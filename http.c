#include "main.h"
#include "http.h"

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
		luaL_error( L, "Plugin_Scr_AddString: parameter 1 must be a string!" );
		return 1;
	}
	char *url = (char *)lua_tostring( L, 1 );
	
	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Scr_AddString: parameter 2 must be a string!" );
		return 1;
	}
	char *data = (char *)lua_tostring( L, 2 );
	
	if( !lua_isstring( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_Scr_AddString: parameter 3 must be a string!" );
		return 1;
	}
	char *callback = (char *)lua_tostring( L, 3 );
	char *method = "POST";
	
	if( n == 4 )
	{
		if( !lua_isstring( L, 4 ) ) 
		{
			luaL_error( L, "Plugin_Scr_AddString: parameter 4 must be a string!" );
			return 1;
		}
		method = (char *)lua_tostring( L, 4 );
	}
	
	lua_httpReq* r;
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
	
	r->callback = callback;
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
				lua_pushstring( LuaVM, NULL );
			}
			Plugin_Lua_pcall( LuaVM, 1, LUA_MULTRET );
			
			lua_settop( LuaVM, 0 );
			
			Plugin_HTTP_FreeObj( r->request );
			r->request = NULL;
			r->callback = NULL;
			
			popRequest( i );
			r = &openRequests[ i ];
			
			continue;
		}
		
		i++;
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

int Q_stricmpn( const char *s1, const char *s2, int n ) 
{
	int		c1, c2;

        if ( s1 == NULL ) {
           if ( s2 == NULL )
             return 0;
           else
             return -1;
        }
        else if ( s2==NULL )
          return 1;



	do {
		c1 = *s1++;
		c2 = *s2++;

		if (!n--) {
			return 0;		// strings are equal until end point
		}

		if (c1 != c2) {
			if (c1 >= 'a' && c1 <= 'z') {
				c1 -= ('a' - 'A');
			}
			if (c2 >= 'a' && c2 <= 'z') {
				c2 -= ('a' - 'A');
			}
			if (c1 != c2) {
				return c1 < c2 ? -1 : 1;
			}
		}
	} while (c1);

	return 0;		// strings are equal
}

int Q_stricmp( const char *s1, const char *s2 ) 
{
	return (s1 && s2) ? Q_stricmpn (s1, s2, 99999) : -1;
}