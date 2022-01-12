#ifndef HTTP_H
#define HTTP_H

#define LUA_HTTP_MAXOPENREQUESTS 64

typedef struct
{
	ftRequest_t* request;
	char* callback;
} lua_httpReq;

void httpInit();
int Lua_HTTP_makeRequest( lua_State *L );
void Lua_HTTP_updateRequests();
void popRequest( int index );

#endif // HTTP_H