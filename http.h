#ifndef HTTP_H
#define HTTP_H

#define LUA_HTTP_MAXOPENREQUESTS 64

typedef struct
{
	ftRequest_t* request;
	int errCode;
	char* callback;
} lua_httpReq;

void httpInit();
int Lua_HTTP_makeRequest( lua_State *L );
void Lua_HTTP_updateRequests();
void popRequest( int index );

int	Q_stricmpn( const char *s1, const char *s2, int n );
int	Q_stricmp( const char *s1, const char *s2 );

#endif // HTTP_H