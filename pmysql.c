#include "main.h"
#include "pmysql.h"
#include "qcommon.h"

static void* pMysqlQuery( void* q );
lua_mysql dbpool[ LUA_MYSQL_MAX_CONNECTIONS ];
cvar_t *stringnil;

void mysqlInit()
{
    stringnil = Plugin_Cvar_RegisterBool( "lua_mysql_stringnil", qfalse, CVAR_INIT, "Represent NULL fields as string nil" );
    mysql_library_init( 0, NULL, NULL );

    // init struct
    for( int i = 0; i < LUA_MYSQL_MAX_CONNECTIONS; i++ )
    {
        dbpool[ i ].pMysql = NULL;
        dbpool[ i ].first_Q = NULL;
        dbpool[ i ].last_Q = NULL;
        dbpool[ i ].first_R = NULL;
        dbpool[ i ].last_R = NULL;
    }

    lua_register( LuaVM, "Plugin_Mysql_Connect", Lua_Mysql_Connect );
    lua_register( LuaVM, "Plugin_Mysql_Query", Lua_Mysql_Query );
    lua_register( LuaVM, "Plugin_Mysql_Close", Lua_Mysql_Close );
}

void Lua_Mysql_Update()
{
    for( int i = 0; i < LUA_MYSQL_MAX_CONNECTIONS; i++ )
    {
        if( dbpool[ i ].first_R != NULL )
        {
            lua_mysql_r *tmp = dbpool[ i ].first_R;
            while( tmp != NULL )
            {
                lua_getglobal( LuaVM, tmp->callback );

                if( tmp->pMysqlRes == NULL && tmp->pMysqlErrNo == 0 )
                {
                    lua_newtable( LuaVM );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "status" );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "num_rows" );
                    lua_pushinteger( LuaVM, tmp->affectedRows );
                    lua_setfield( LuaVM, -2, "affected_rows" );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "num_fields" );
                }
                else if( tmp->pMysqlErrNo == 0 && tmp->pMysqlRes != NULL )
                {  
                    lua_newtable( LuaVM );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "status" );

                    int numrows = mysql_num_rows( tmp->pMysqlRes );
                    lua_pushinteger( LuaVM, numrows );
                    lua_setfield( LuaVM, -2, "num_rows" );

                    lua_pushinteger( LuaVM, tmp->affectedRows );
                    lua_setfield( LuaVM, -2, "affected_rows" );

                    int numfields = mysql_num_fields( tmp->pMysqlRes );
                    lua_pushinteger( LuaVM, numfields );
                    lua_setfield( LuaVM, -2, "num_fields" );

                    MYSQL_FIELD *field;
                    char **keyFields = malloc( sizeof( char* ) * numfields );

                    int arridx = 0;
                    while( ( field = mysql_fetch_field( tmp->pMysqlRes ) ) != NULL )
                    {
                        keyFields[ arridx ] = Q_Strcpy( field->name );
                        arridx++;
                    }

                    MYSQL_ROW row = NULL;
                    arridx = 1;
                    while( ( row = mysql_fetch_row( tmp->pMysqlRes ) ) != NULL )
                    {
                        lua_newtable( LuaVM ); // {}o, {}n

                        for( int j = 0; j < numfields; j++ )
                        {
                            if( row[ j ] != NULL )
                            {
                                lua_pushstring( LuaVM, row[ j ] );
                                lua_setfield( LuaVM, -2, keyFields[ j ] );
                            }
                            else if( Plugin_Cvar_GetBoolean( stringnil ) )
                            {
                                // pushing nil is same as not creating table field in the first place
                                // pushing string "nil" instead
                                lua_pushstring( LuaVM, "nil" ); // {}o, {}n, "nil"
                                lua_setfield( LuaVM, -2, keyFields[ j ] ); // {}o, {}n
                            }
                        }

                        lua_pushinteger( LuaVM, arridx ); // {}o, {}n, arridx
                        lua_insert( LuaVM, -2 ); // {}o, arridx, {}n
                        lua_settable( LuaVM, -3 ); // {}o

                        arridx++;
                    }

                    for( int j = 0; j < numfields; j++ )
                    {
                        free( keyFields[ j ] );
                    }
                    free( keyFields );
                }
                else
                {
                    lua_newtable( LuaVM );
                    lua_pushinteger( LuaVM, tmp->pMysqlErrNo );
                    lua_setfield( LuaVM, -2, "status" );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "num_rows" );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "affected_rows" );
                    lua_pushinteger( LuaVM, 0 );
                    lua_setfield( LuaVM, -2, "num_fields" );
                }

                Plugin_Lua_pcall( LuaVM, 1, LUA_MULTRET );
        
                lua_settop( LuaVM, 0 );

                Plugin_EnterCriticalSection();

                tmp = tmp->next;
                dequeueResult( &dbpool[ i ] );

                Plugin_LeaveCriticalSection();
            }
        }
    }
}

int Lua_Mysql_Close( lua_State *L )
{
    int n = lua_gettop( L );
	
	if( n != 1 )
	{
		luaL_error( L, "Plugin_Mysql_Close: Function requires 1 parameter!" );
		return 1;
	}

    if( !lua_isnumber( L, 1 ) )
    {
        luaL_error( L, "Plugin_Mysql_Close: parameter 1 must be an integer!" );
		return 1;
    }
    int handle = lua_tointeger( L, 1 );

    if( !checkConnection( handle ) )
    {
        luaL_error( L, "Plugin_Mysql_Close: invalid handle!" );
        return 1;
    }

    lua_mysql *sqlhandle = &dbpool[ handle ];

    // Let open queries finish
    // Plugin_Mysql_Query is same thread so new ones can't be started
    while( sqlhandle->first_Q != NULL )
    {
        Plugin_SleepMSec( 5 );
    }

    // results get popped in update
    mysql_close( sqlhandle->pMysql );
    sqlhandle->pMysql = NULL;

    return 0;
}

int Lua_Mysql_Connect( lua_State *L )
{
    int handle = -1;
    for( int i = 0; i < LUA_MYSQL_MAX_CONNECTIONS; i++ )
    {
        if( !dbpool[ i ].pMysql )
        {
            handle = i;
            break;
        }
    }

    if( handle < 0 )
    {
        Plugin_DPrintf( "Lua Mysql: max open connections reached!\n" );
		lua_pushnil( L );
		return 1;
    }

    lua_mysql *sqlhandle = &dbpool[ handle ];

    int n = lua_gettop( L );
	
	if( n < 4 )
	{
		luaL_error( L, "Plugin_Mysql_Connect: Function requires 4 parameters!" );
		return 1;
	}

    if( !lua_isstring( L, 1 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Connect: parameter 1 must be a string!" );
		return 1;
	}
	char *host = (char *)lua_tostring( L, 1 );

    if( !Q_stricmp( host, "localhost" ) )
    {
        host = "127.0.0.1";
    }
	
	if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Connect: parameter 2 must be a string!" );
		return 1;
	}
	char *user = (char *)lua_tostring( L, 2 );
	
	if( !lua_isstring( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Connect: parameter 3 must be a string!" );
		return 1;
	}
	char *pass = (char *)lua_tostring( L, 3 );

    if( !lua_isstring( L, 4 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Connect: parameter 4 must be a string!" );
		return 1;
	}
	char *db = (char *)lua_tostring( L, 4 );

    if( db[0] == '\0' )
    {
        db = 0;
    }

    int port = 3306;

    if( n == 5 )
    {
        if( !lua_isnumber( L, 5 ) ) 
        {
            luaL_error( L, "Plugin_Mysql_Connect: parameter 5 must be an integer!" );
            return 1;
        }
        port = lua_tointeger( L, 5 );
    }

    sqlhandle->pMysql = mysql_init( sqlhandle->pMysql );
    if( sqlhandle->pMysql == NULL )
    {
        Plugin_PrintError( "********\nMySql init failed! \nhandle: %i \nErrNo: %i \nErr: %s \n********\n", handle, 
                            mysql_errno( sqlhandle->pMysql ), mysql_error( sqlhandle->pMysql ) );
        lua_pushnil( L );
		return 1;
    }

    qboolean reconnect = qtrue;
    mysql_options( sqlhandle->pMysql, MYSQL_OPT_RECONNECT, &reconnect );

    if( mysql_real_connect( sqlhandle->pMysql, host, user, pass, db, port, NULL, 0 ) == NULL )
    {
        Plugin_PrintError( "********\nMySql connect failed! \nhandle: %i \nErrNo: %i \nErr: %s \n********\n", handle, 
                            mysql_errno( sqlhandle->pMysql ), mysql_error( sqlhandle->pMysql ) );
        lua_pushnil( L );
		return 1;
    }

    lua_pushinteger( L, handle );
    return 1;
}

int Lua_Mysql_Query( lua_State *L )
{
    int n = lua_gettop( L );
	
	if( n < 3 )
	{
		luaL_error( L, "Plugin_Mysql_Query: Function requires 3 parameters!" );
		return 1;
	}

    if( !lua_isnumber( L, 1 ) )
    {
        luaL_error( L, "Plugin_Mysql_Query: parameter 1 must be an integer!" );
		return 1;
    }
    int handle = lua_tointeger( L, 1 );

    if( !lua_isstring( L, 2 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Query: parameter 2 must be a string!" );
		return 1;
	}
    char *callback = (char *)lua_tostring( L, 2 );

    if( !lua_isstring( L, 3 ) ) 
	{
		luaL_error( L, "Plugin_Mysql_Query: parameter 3 must be a string!" );
		return 1;
	}
    char *query = (char *)lua_tostring( L, 3 );

    if( !checkConnection( handle ) )
    {
        lua_pushnil( L );
        return 1;
    }

    lua_mysql *sqlhandle = &dbpool[ handle ];

    lua_mysql_q *tmp = malloc( sizeof( lua_mysql_q ) );
    if( tmp == NULL )
    {
        Plugin_PrintError( "Lua Mysql: Failed to alloc memory!\n" );
        lua_pushnil( L );
        return 1;
    }

    tmp->callback = Q_Strcpy( callback );
    if( tmp->callback == NULL )
    {
        lua_pushnil( L );
        return 1;
    }
    tmp->query = Q_Strcpy( query );
    if( tmp->query == NULL )
    {
        lua_pushnil( L );
        return 1;
    }
    tmp->handle = handle;
    tmp->next = NULL;

    Plugin_EnterCriticalSection();

    if( sqlhandle->first_Q == NULL ) // Queue is empty
    {
        sqlhandle->first_Q = tmp;
        sqlhandle->last_Q = tmp;

        if( Plugin_CreateNewThread( pMysqlQuery, NULL, (void*)sqlhandle ) == qfalse )
        {
            free( tmp->query );
            free( tmp->callback );
            free( tmp );

            sqlhandle->first_Q = NULL;
            sqlhandle->last_Q = NULL;

            Plugin_LeaveCriticalSection();

            Plugin_PrintError( "Lua Mysql: Failed to start thread!\n" );
            lua_pushnil( L );
            return 1;
        }
    }
    else
    {
        sqlhandle->last_Q->next = tmp;
        sqlhandle->last_Q = sqlhandle->last_Q->next;
    }

    Plugin_LeaveCriticalSection();

    lua_pushinteger( L, 1 );
    return 1;
}

static void* pMysqlQuery( void* q )
{
    lua_mysql *sqlhandle = (lua_mysql*)q;
    lua_mysql_q *tmp = sqlhandle->first_Q;
    lua_mysql_r *res;

    while( tmp != NULL )
    {
        res = malloc( sizeof( lua_mysql_r ) );
        res->callback = tmp->callback;
        res->next = NULL;
        res->affectedRows = 0;

        if( mysql_query( sqlhandle->pMysql, tmp->query ) == 0 )
        {
            res->pMysqlRes = mysql_store_result( sqlhandle->pMysql );

            res->pMysqlErrNo = mysql_errno( sqlhandle->pMysql );

            if( res->pMysqlRes == NULL && res->pMysqlErrNo != 0 )
            {
                Plugin_PrintError( "********\nMySql query failed! \nhandle: %i \nErrNo: %i \nErr: %s \nQuery: %s \n********\n", 
                                tmp->handle, res->pMysqlErrNo, mysql_error( sqlhandle->pMysql ), tmp->query );
            }
            else
            {
                res->affectedRows = mysql_affected_rows( sqlhandle->pMysql );
            }
        }
        else
        {
            res->pMysqlErrNo = mysql_errno( sqlhandle->pMysql );
            res->pMysqlRes = NULL;

            Plugin_PrintError( "********\nMySql query failed! \nhandle: %i \nErrNo: %i \nErr: %s \nQuery: %s \n********\n", 
                                tmp->handle, res->pMysqlErrNo, mysql_error( sqlhandle->pMysql ), tmp->query );
        }

        Plugin_EnterCriticalSection();

        if( sqlhandle->first_R == NULL ) // Queue is empty
        {
            sqlhandle->first_R = res;
            sqlhandle->last_R = res;
        }
        else
        {
            sqlhandle->last_R->next = res;
            sqlhandle->last_R = sqlhandle->last_R->next;
        }

        tmp = tmp->next;
        dequeueQuery( sqlhandle );

        Plugin_LeaveCriticalSection();
    }

    return NULL;
}

void dequeueQuery( lua_mysql *sqlhandle )
{
    if( sqlhandle->first_Q != NULL )
    {
        lua_mysql_q *tmp;
        tmp = sqlhandle->first_Q;
        sqlhandle->first_Q = sqlhandle->first_Q->next;
        free( tmp->query );
        free( tmp );
    }
}

void dequeueResult( lua_mysql *sqlhandle )
{
    if( sqlhandle->first_R != NULL )
    {
        lua_mysql_r *tmp;
        tmp = sqlhandle->first_R;
        sqlhandle->first_R = sqlhandle->first_R->next;

        if( tmp->pMysqlRes != NULL )
        {
            mysql_free_result( tmp->pMysqlRes );
        }

        free( tmp->callback );
        free( tmp );
    }
}

qboolean checkConnection( int handle )
{
    if( handle < 0 || handle > LUA_MYSQL_MAX_CONNECTIONS )
    {
        Plugin_PrintError( "Lua Mysql: Incorrect handle!\n" );
        return qfalse;
    }
    else if( dbpool[ handle ].pMysql == NULL )
    {
        Plugin_PrintError( "Lua Mysql: uninitialized connection!\n" );
        return qfalse;
    }

    return qtrue;
}