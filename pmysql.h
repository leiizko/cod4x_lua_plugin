#ifndef PMYSQL_H
#define PMYSQL_H

#include <mysql.h>

#define LUA_MYSQL_MAX_CONNECTIONS 4

typedef struct lua_mysql_q lua_mysql_q;
typedef struct lua_mysql_r lua_mysql_r;

struct lua_mysql_q
{
	unsigned int handle;
    char *callback;
    char *query;
    lua_mysql_q *next;
};

struct lua_mysql_r
{
    MYSQL_RES *pMysqlRes;
    char *callback;
    unsigned int pMysqlErrNo;
    unsigned int affectedRows;
    lua_mysql_r *next;
};

typedef struct
{
	MYSQL *pMysql;
    lua_mysql_q *first_Q;
    lua_mysql_q *last_Q;
    lua_mysql_r *first_R;
    lua_mysql_r *last_R;
} lua_mysql;

int Lua_Mysql_Connect( lua_State *L );
int Lua_Mysql_Query( lua_State *L );
int Lua_Mysql_Close( lua_State *L );

void mysqlInit();
void Lua_Mysql_Update();
void dequeueQuery( lua_mysql *sqlhandle );
void dequeueResult( lua_mysql *sqlhandle );
qboolean checkConnection( int handle );

#endif // PMYSQL_H