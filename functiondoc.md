# Function reference
_Disclaimer: Information included here may be incomplete and/or not necessarily true at the time you're reading it.
We do our best to keep it updated._

## Table of Contents
1. [Register functions](#register-functions)
    - [Plugin_AddCommand](#plugin_addcommand-char-commandname-int-power-)
    - [Plugin_ScrAddFunction](#plugin_scraddfunction-char-functionname-)
    - [Plugin_ScrAddMethod](#plugin_scraddmethod-char-methodname-)
2. [Get functions](#get-functions)
    - [Plugin_Scr_GetNumParam](#plugin_scr_getnumparam)
    - [Plugin_Scr_GetEntity](#plugin_scr_getentity-int-paramnum-)
    - [Plugin_Scr_GetInt](#plugin_scr_getint-int-paramnum-)
    - [Plugin_Scr_GetFloat](#plugin_scr_getfloat-int-paramnum-)
    - [Plugin_Scr_GetVector](#plugin_scr_getvector-int-paramnum-)
    - [Plugin_Scr_GetType](#plugin_scr_gettype-int-paramnum-)
    - [Plugin_Scr_GetString](#plugin_scr_getstring-int-paramnum-)
    - [Plugin_Scr_GetFunc](#plugin_scr_getfunc-int-paramnum-)
    - [Plugin_Cmd_GetInvokerSlot](#plugin_cmd_getinvokerslot)
    - [Plugin_Cmd_Argc](#plugin_cmd_argc)
    - [Plugin_Cmd_Args](#plugin_cmd_args)
    - [Plugin_Cmd_Argv](#plugin_cmd_argv)
3. [Add functions](#add-functions)
    - [Plugin_Scr_AddEntity](#plugin_scr_addentity-gentity_t-ent)
    - [Plugin_Scr_AddInt](#plugin_scr_addint-int-num-)
    - [Plugin_Scr_AddFloat](#plugin_scr_addfloat-float-num-)
    - [Plugin_Scr_AddBool](#plugin_scr_addbool-qboolean-bool-)
    - [Plugin_Scr_AddString](#plugin_scr_addstring-char-str-)
    - [Plugin_Scr_AddVector](#plugin_scr_addvector-vec3_t-vec3-)
    - [Plugin_Scr_AddUndefined](#plugin_scr_addundefined)
    - [Plugin_Scr_MakeArray](#plugin_scr_makearray)
    - [Plugin_Scr_AddArray](#plugin_scr_addarray)
    - [Plugin_Scr_AddArrayStringIndexed](#plugin_scr_addarraystringindexed-int-stridx-)
4. [Thread functions](#thread-functions)
    - [Plugin_Scr_FreeThread](#plugin_scr_freethread-int-threadid-)
    - [Plugin_Scr_ExecThread](#plugin_scr_execthread-int-callbackhook-int-numparams-)
    - [Plugin_Scr_ExecEntThread](#plugin_scr_execentthread-gentity_t-ent-int-callbackhook-int-numparams-)
5. [Utility functions](#utility-functions)
    - [Plugin_Printf](#plugin_printf-const-char-str-)
    - [Plugin_DPrintf](#plugin_dprintf-const-char-str-)
    - [Plugin_GetVersion](#plugin_getversion-)
    - [Plugin_Milliseconds](#plugin_milliseconds-)
    - [Plugin_Scr_Error](#plugin_scr_error-const-char-str-)
    - [Plugin_Scr_ParamError](#plugin_scr_paramerror-int-paramnum-const-char-str-)
    - [Plugin_Scr_ObjectError](#plugin_scr_objecterror-const-char-str-)
    - [Plugin_Error](#plugin_error-int-code-const-char-str-)
    - [Plugin_GetGentityForClientNum](#plugin_getgentityforclientnum-int-clientnum-)
    - [Plugin_GetClientNumForGentity](#plugin_getclientnumforgentity-gentity_t-ent-)
    - [Plugin_GetPlayerName](#plugin_getplayername-int-clientnum-)
    - [Plugin_GetClientScoreboard](#plugin_getclientscoreboard-int-clientnum-)
    - [Plugin_Scr_AllocString](#plugin_scr_allocstring-const-char-str-)
    - [Plugin_SV_GetConfigstring](#plugin_sv_getconfigstring-int-index-)
    - [Plugin_SV_SetConfigstring](#plugin_sv_setconfigstring-int-index-const-char-str-)
    - [Plugin_DropClient](#plugin_dropclient-int-clientnum-const-char-reason-)
    - [Plugin_BanClient](#plugin_banclient-int-clientnum-int-minutes-int-invokerid-const-char-reason-)
6. [Notify functions](#notify-functions)
    - [Plugin_Scr_NotifyLevel](#plugin_scr_notifylevel-int-stridx-int-paramnum-)
    - [Plugin_Scr_Notify](#plugin_scr_notify-gentity_t-ent-int-stridx-int-paramnum-)
7. [ICONV functions](#iconv-functions)
    - [Plugin_iconv_open](#plugin_iconv_open-char-to-char-from-)
    - [Plugin_iconv_close](#plugin_iconv_close-int-conversionIndex-)
    - [Plugin_iconv](#plugin_iconv-int-conversionIndex-char-str-)
8. [CVAR functions](#cvar-functions)
    - [Plugin_Cvar_RegisterString](#plugin_cvar_registerstring-char-varname-char-varvalue-int-flags-char-vardesc-)
    - [Plugin_Cvar_RegisterBool](#plugin_cvar_registerbool-char-varName-qboolean-varValue-int-flags-char-varDesc-)
    - [Plugin_Cvar_RegisterInt](#plugin_cvar_registerint-char-varName-int-value-int-minvalue-int-maxvalue-int-flags-char-varDesc-)
    - [Plugin_Cvar_RegisterFloat](#plugin_cvar_registerfloat-char-varName-float-value-float-minvalue-float-maxvalue-int-flags-char-varDesc-)
    - [Plugin_Cvar_SetString](#plugin_cvar_setstring-convar_t-cvar-char-value-)
    - [Plugin_Cvar_SetBool](#plugin_cvar_setbool-convar_t-cvar-qboolean-value-)
    - [Plugin_Cvar_SetInt](#plugin_cvar_setint-convar_t-cvar-int-value-)
    - [Plugin_Cvar_SetFloat](#plugin_cvar_setfloat-convar_t-cvar-float-value-)
    - [Plugin_Cvar_GetString](#plugin_cvar_getstring-convar_t-cvar-)
    - [Plugin_Cvar_GetBool](#plugin_cvar_getbool-convar_t-cvar-)
    - [Plugin_Cvar_GetInt](#plugin_cvar_getint-convar_t-cvar-)
    - [Plugin_Cvar_GetFloat](#plugin_cvar_getfloat-convar_t-cvar-)
    - [Plugin_Cvar_VariableStringBuffer](#plugin_cvar_variablestringbuffer-char-varname-)
    - [Plugin_Cvar_VariableValue](#plugin_cvar_variablevalue-char-varname-)
    - [Plugin_Cvar_VariableIntegerValue](#plugin_cvar_variableintegervalue-char-varname-)
    - [Plugin_Cvar_VariableBooleanValue](#plugin_cvar_variablebooleanvalue-char-varname-)
    - [Plugin_Cvar_Set](#plugin_cvar_set-char-varName-char-value-)
9. [HTTP function](#http-function)
    - [Plugin_HTTP_makeRequest](#plugin_http_makerequest-char-url-char-data-char-callback-char-method-)
10. [MySQL functions](#mysql-functions)
    - [Plugin_Mysql_Connect](#plugin_mysql_connect-char-host-char-user-char-password-char-db-int-port-)
    - [Plugin_Mysql_Query](#plugin_mysql_query-int-handle-char-callback-char-query-)
    - [Plugin_Mysql_Close](#plugin_mysql_close-int-handle-)

## Register functions
These functions are used to add script functions or commands to gsc.

#### Plugin_AddCommand( char *commandName, int power )

Registers a command with commandName and required power points. Power with value 0 means rcon only, 1 is for everyone and rest is based on set power point.

Usage example:
Lua:
```lua
Plugin_AddCommand( "foo", 1 )

function foo()

    -- Player types $foo in chat, this function gets called
    -- do whatever.
end
```

#### Plugin_ScrAddFunction( char *functionName )

Registers a script function with functionName. There must be a lua function with same name.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    -- do whatever.
end
```
Gsc:
```c
init()
{
    foo();
}
```

#### Plugin_ScrAddMethod( char *methodName )

Registers a method with methodName, lua function must be of same name. **Player** entity must call this function or it will result into script error. Gentity_t* gets passed into lua function - be careful if you decide to store gentity_t* somewhere as the pointer could become invalid, best practice is to deal with client num instead.

Usage example:
Lua:
```lua
Plugin_ScrAddMethod( "foo" )

function foo( gentity )

    -- do whatever.
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo();
}
```

## Get functions

Used to retrieve parameters from gsc, where paramNum is parameter index and starts at 0. 

#### Plugin_Scr_GetNumParam()

Returns number of function parameters.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    n = Plugin_Scr_GetNumParam() -- in this example returns 5. You can see indexes in gsc code.
end
```
Gsc:
```c
init()
{
    foo( 0, 1, 2, 3, 4 );
}
```

#### Plugin_Scr_GetEntity( int paramNum )

Retrieves a gentity_t* - be careful if you decide to store gentity_t* somewhere as the pointer could become invalid, best practice is to deal with client num instead. Notice how this is used to get gentity_t* as a gsc function parameter, where as a method gets it as lua function parameter.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    gentity = Plugin_Scr_GetEntity( 0 )
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    foo( player );
}
```

#### Plugin_Scr_GetInt( int paramNum )

Retrieves an integer from gsc.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    gentity = Plugin_Scr_GetEntity( 0 )
    i = Plugin_Scr_GetInt( 1 ) -- index is now 1 as param is second in gsc
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    foo( player, 123 );
}
```

#### Plugin_Scr_GetFloat( int paramNum )

Retrieves a float from gsc.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    f = Plugin_Scr_GetFloat( 0 )
end
```
Gsc:
```c
init()
{
    foo( 1.23 );
}
```

#### Plugin_Scr_GetVector( int paramNum )

Retrieves a vector from gsc.
Extra notes about vectors in Lua:
* Vector is a table with size of 3
* Index must always start at 1 ( vec[1], vec[2], vec[3] ) - they start at index 0 in gsc!
* You can simply define the vector as `vec = { 192.27, 946.5, 2895.99 }`

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    vec3 = Plugin_Scr_GetVector( 0 )
    sum = vec[ 1 ] + vec[ 2 ] + vec[ 3 ]
end
```
Gsc:
```c
init()
{
    foo( {1, 2, 3} );
}
```

#### Plugin_Scr_GetType( int paramNum )

Gets a type of parameter - type is an integer.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    type = Plugin_Scr_GetType( 0 )
end
```
Gsc:
```c
init()
{
    foo( {1, 2, 3} );
}
```

List of types:
```
VAR_UNDEFINED = 0x0,
VAR_BEGIN_REF = 0x1,
VAR_POINTER = 0x1,
VAR_STRING = 0x2,
VAR_ISTRING = 0x3,
VAR_VECTOR = 0x4,
VAR_END_REF = 0x5,
VAR_FLOAT = 0x5,
VAR_INTEGER = 0x6,
VAR_CODEPOS = 0x7,
VAR_PRECODEPOS = 0x8,
VAR_FUNCTION = 0x9,
VAR_STACK = 0xA,
VAR_ANIMATION = 0xB,
VAR_DEVELOPER_CODEPOS = 0xC,
VAR_INCLUDE_CODEPOS = 0xD,
VAR_THREAD = 0xE,
VAR_NOTIFY_THREAD = 0xF,
VAR_TIME_THREAD = 0x10,
VAR_CHILD_THREAD = 0x11,
VAR_OBJECT = 0x12,
VAR_DEAD_ENTITY = 0x13,
VAR_ENTITY = 0x14,
VAR_ARRAY = 0x15,
VAR_DEAD_THREAD = 0x16,
VAR_COUNT = 0x17,
VAR_THREAD_LIST = 0x18,
VAR_ENDON_LIST = 0x19
```

#### Plugin_Scr_GetString( int paramNum )

Retrieves a string from gsc.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    str = Plugin_Scr_GetString( 0 )
end
```
Gsc:
```c
init()
{
    foo( "Hello!" );
}
```

#### Plugin_Scr_GetFunc( int paramNum )

Retrieves a function handle from gsc - function handle is an integer!. This is used in script threads/callbacks.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    callbackhook = Plugin_Scr_GetFunc( 0 )
end
```
Gsc:
```c
init()
{
    foo( ::callback );
}

callback( arg1, arg2 )
{
    // number of args is defined when calling the function from lua - could be none or several.
}
```

#### Plugin_Cmd_GetInvokerSlot()

Retrieves player slot of a player, who envoked the command.

Usage example:
Lua:
```lua
Plugin_AddCommand( "foo", 1 )

function foo()

    -- Player types $foo in chat, this function gets called
    clientNum = Plugin_Cmd_GetInvokerSlot()
end
```

#### Plugin_Cmd_Argc()

Returns number of arguments supplied with command. Arguments are tokenized string of parameters from invoked command

Usage example:
Lua:
```lua
Plugin_AddCommand( "foo", 1 )

function foo()

    -- Player types $foo in chat, this function gets called
    -- $foo adding new params
    --        ^     ^    ^
    argNum = Plugin_Cmd_Argc() -- returns 3
end
```

#### Plugin_Cmd_Args()

Returns entire untokenized string of arguments from invoked command

Usage example:
Lua:
```lua
Plugin_AddCommand( "foo", 1 )

function foo()

    -- Player types $foo in chat, this function gets called
    -- $foo adding new params
    --        ^     ^    ^
    str = Plugin_Cmd_Args() -- returns "adding new params"
end
```

#### Plugin_Cmd_Argv( int paramNum )

Returns a single tokenized argument from invoked command with index.

Usage example:
Lua:
```lua
Plugin_AddCommand( "foo", 1 )

function foo()

    -- Player types $foo in chat, this function gets called
    -- $foo adding new params
    --        ^     ^    ^
    arg = Plugin_Cmd_Argv( 1 ) -- returns "new"
end
```

## Add functions

Used to return specified type from lua to gsc. You can only return a single type to gsc.

#### Plugin_Scr_AddEntity( gentity_t *ent )

Adds gentity_t* to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    gentity = Plugin_GetGentityForClientNum( 10 ) -- returns gentity for client slot 10
    Plugin_Scr_AddEntity( gentity )
end
```
Gsc:
```c
init()
{
    num = foo(); // Returns gentity
}
```

#### Plugin_Scr_AddInt( int num )

Adds integer to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Plugin_Scr_AddInt( 10 )
end
```
Gsc:
```c
init()
{
    num = foo(); // Returns 10
}
```

#### Plugin_Scr_AddFloat( float num )

Adds float to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Plugin_Scr_AddFloat( 1.23 )
end
```
Gsc:
```c
init()
{
    float = foo(); // Returns 1.23
}
```

#### Plugin_Scr_AddBool( qboolean bool )

Adds boolean to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Lua_Scr_AddBool( true )
end
```
Gsc:
```c
init()
{
    if( foo() ) // Returns true
    {
        // ....
    }
}
```

#### Plugin_Scr_AddString( char *str )

Adds string to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Plugin_Scr_AddString( "hello" )
end
```
Gsc:
```c
init()
{
    str = foo(); // Returns "hello"
}
```

#### Plugin_Scr_AddVector( vec3_t vec3 )

Adds vector to gsc function.
Extra notes about vectors in Lua:
* Vector is a table with size of 3
* Index must always start at 1 ( vec[1], vec[2], vec[3] )
* You can simply define the vector as `vec = { 192.27, 946.5, 2895.99 }`

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    vec = { 192.27, 946.5, 2895.99 }
    Plugin_Scr_AddVector( vec )
end
```
Gsc:
```c
init()
{
    vec3 = foo(); // Returns { 192.27, 946.5, 2895.99 }
}
```

#### Plugin_Scr_AddUndefined()

Adds undefined to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Plugin_Scr_AddUndefined()
end
```
Gsc:
```c
init()
{
    if( !isDefined( foo() ) ) // Returns undefined
    {
        // ....
    }
}
```

#### Plugin_Scr_MakeArray()
#### Plugin_Scr_AddArray()

These functions are used to add array to gsc. First Plugin_Scr_MakeArray() must be used, followed by [Add function](#add-functions) and finished by Plugin_Scr_AddArray().
It is also possible to add multi-dimensional arrays by nesting Plugin_Scr_MakeArray() function.

Adds boolean to gsc function.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )
Plugin_ScrAddFunction( "foo2D" )

function foo()

    Plugin_Scr_MakeArray()
    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 2 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 3 )
    Plugin_Scr_AddArray()
end

function foo2D()

    Plugin_Scr_MakeArray()
    Plugin_Scr_MakeArray()
    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 2 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 3 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddArray()
    Plugin_Scr_MakeArray()
    Plugin_Scr_AddInt( 4 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 5 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddInt( 6 )
    Plugin_Scr_AddArray()
    Plugin_Scr_AddArray()
end
```
Gsc:
```c
init()
{
    arr = foo(); // returns arr[ 0 ] = 1, arr[ 1 ] = 2, ...

    arr2d = foo2D(); // returns arr[ 0 ][ 0 ] = 1, arr[ 1 ][ 1 ] = 5, ...
}
```

#### Plugin_Scr_AddArrayStringIndexed( int strIdx )

Function used to add array to gsc with string index. First Plugin_Scr_MakeArray() must be used, followed by [Add function](#add-functions) and finished by Plugin_Scr_AddArrayStringIndexed( int strIdx ), where strIdx must be provided by Plugin_Scr_AllocString( char* str ). You may nest arrays as in previous example.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    strIdx1 = Plugin_Scr_AllocString( "index1" )
    strIdx2 = Plugin_Scr_AllocString( "anotherIndex" )

    Plugin_Scr_MakeArray()
    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddArrayStringIndexed( strIdx1 )
    Plugin_Scr_AddInt( 2 )
    Plugin_Scr_AddArrayStringIndexed( strIdx2 )
end
```
Gsc:
```c
init()
{
    arr = foo(); // returns arr[ "index1" ] = 1, arr[ "anotherIndex" ] = 2
}
```

## Thread functions

Functions used to create a gsc thread/callback.

#### Plugin_Scr_FreeThread( int threadId )

Frees thread with threadId. All created threads must be freed.

#### Plugin_Scr_ExecThread( int callbackhook, int numParams )

Creates a gsc thread with specified parameter number. You can return different types of parameters.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    callbackhook = Plugin_Scr_GetFunc( 0 )

    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddString( "whatever" )
    thread = Plugin_Scr_ExecThread( callbackhook, 2 )

    Plugin_Scr_FreeThread( thread )
end
```
Gsc:
```c
init()
{
    foo( ::callback );
}

callback( arg1, arg2 )
{
    // number of args is defined when calling the function from lua - could be none or several.
}
```

#### Plugin_Scr_ExecEntThread( gentity_t *ent, int callbackhook, int numParams )

Creates a gsc thread with specified parameter number and entity (self in callback is the specified entity, meanwhile Plugin_Scr_ExecThread( int callbackhook, int numParams ) self is level object). You can return different types of parameters.

Usage example:
Lua:
```lua
Plugin_ScrAddMethod( "foo" )

function foo( gentity )

    callbackhook = Plugin_Scr_GetFunc( 0 )

    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddString( "whatever" )
    Plugin_Scr_AddString( "Third arg!" )
    thread = Plugin_Scr_ExecEntThread( gentity, callbackhook, 3 )

    Plugin_Scr_FreeThread( thread )
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo( ::callback );
}

callback( arg1, arg2, arg3 )
{
    print( self.name ) // prints player name
    // number of args is defined when calling the function from lua - could be none or several.
}
```

## Utility functions

Functions that return various things and compliment other functionality.

#### Plugin_Printf( const char *str )

Prints string to console

Usage example:
Lua:
```lua
str = "World!"

Plugin_Printf( "Hello " .. str .. "\n" ) -- prints Hello World! to console
```

#### Plugin_DPrintf( const char *str )

Prints string to console when developer mode is enabled.

Usage example:
Lua:
```lua
Plugin_Printf( "I am only visible in developer mode!" )
```

#### Plugin_GetVersion()

Returns plugin version as float.

Usage example:
Lua:
```lua
ver = Plugin_GetVersion() -- example returns 0.5
```

#### Plugin_Milliseconds()

Returns time since server start in miliseconds.

Usage example:
Lua:
```lua
timeElapsed = Plugin_Milliseconds()
```

#### Plugin_Scr_Error( const char *str )

Prints a script runtime error to console.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    Plugin_Scr_Error( "Depricated! use foo2() instead!\n" )
end
```
Gsc:
```c
init()
{
    arr = foo();
}
```

#### Plugin_Scr_ParamError( int paramNum, const char *str )

Prints a script runtime error for parameter with paramNum.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    type = Plugin_Scr_GetType( 0 )

    if( type != 2)
        Plugin_Scr_ParamError( 0, "Parameter 1 must be a string!\n" )
end
```
Gsc:
```c
init()
{
    arr = foo();
}
```

#### Plugin_Scr_ObjectError( const char *str )

Prints a script runtime error for object. Not really useful as plugin C functions already raise this if applicable.

#### Plugin_Error( int code, const char *str )

Raises plugin error. Actions depend on code parameter:
0 = Raises a plugin warning
1 = Disabled the plugin
2 = Terminates the server

Usage example:
Lua:
```lua
if somethingBadHappened then
    Plugin_Error( 2, "Critical error because something bad happened" )
end
```

#### Plugin_GetGentityForClientNum( int clientNum )

Returns gentity for specified clientNum.

Usage example:
Lua:
```lua
Plugin_ScrAddFunction( "foo" )

function foo()

    callbackhook = Plugin_Scr_GetFunc( 0 )
    clientNum = Plugin_Scr_GetInt( 1 )

    gentity = Plugin_GetGentityForClientNum( clientNum )

    Plugin_Scr_AddInt( 1 )
    Plugin_Scr_AddString( "whatever" )
    Plugin_Scr_AddString( "Third arg!" )
    thread = Plugin_Scr_ExecEntThread( gentity, callbackhook, 3 )

    Plugin_Scr_FreeThread( thread )
end
```
Gsc:
```c
init()
{
    foo( ::callback, clientNum );
}

callback( arg1, arg2, arg3 )
{
    print( self.name ) // prints player name
    // number of args is defined when calling the function from lua - could be none or several.
}
```

#### Plugin_GetClientNumForGentity( gentity_t *ent )

Returns a client number for specified gentity_t*.

Usage example:
Lua:
```lua
Plugin_ScrAddMethod( "foo" )

function foo( gentity )

    clientNum = Plugin_GetClientNumForGentity( gentity )
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo();
}
```

#### Plugin_GetPlayerName( int clientNum )

Returns player name for specified clientNum

Usage example:
Lua:
```lua
Plugin_ScrAddMethod( "foo" )

function foo( gentity )

    clientNum = Plugin_GetClientNumForGentity( gentity )
    playerName = Plugin_GetPlayerName( clientNum )
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo();
}
```

#### Plugin_GetClientScoreboard( int clientNum )

Returns scoreboard ( kills, assists, deaths and score ) for specified clientNum

Usage example:
Lua:
```lua
Plugin_ScrAddMethod( "foo" )

function foo( gentity )

    clientNum = Plugin_GetClientNumForGentity( gentity )
    scoreboard = Plugin_GetClientScoreboard( clientNum )
    --[[
    returns table with following indexes:
    scoreboard.kills
    scoreboard.assists
    scoreboard.deaths
    scoreboard.score
    ]]--
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo();
}
```

#### Plugin_Scr_AllocString( const char *str )

Allocates string and returns its index. Strings must be reallocated each time map rotates or fully restarts - use OnSpawnServer event.

Usage example:
Lua:
```lua
allocatedStrings = {}

--[[ 
Called on gametype start - Each time map fully restarts or rotates
]]--
function OnSpawnServer ()

    allocatedStrings.arrayindex_kda = Plugin_Scr_AllocString( "KDA" )
    allocatedStrings.notifyindex_clientupdate = Plugin_Scr_AllocString( "client_update" )
    -- ....
end
```

#### Plugin_SV_GetConfigstring( int index )

Returns config string with index.

Usage example:
Lua:
```lua
    configstring = Plugin_SV_GetConfigstring( 110 )
```

#### Plugin_SV_SetConfigstring( int index, const char* str )

Sets config string with index

Usage example:
Lua:
```lua
    Plugin_SV_SetConfigstring( 110, "newstring" )
```

#### Plugin_DropClient( int clientNum, const char* reason )

Kicks a player with clientNum for specified reason.

Usage example:
Lua:
```lua
    Plugin_DropClient( 10, "You are AFK!" )
```

#### Plugin_BanClient( int clientNum, int minutes, int invokerid, const char* reason )

Bans client with clientNum for specified lenghts in minutes for specified reason.
Minutes can be -1 for permanent ban or any other specified lenght.
InvokerID can be 0 or numeric UID.

Usage example:
Lua:
```lua
    Plugin_BanClient( 10, -1, 0, "Cheating" ) --perm ban
```

## Notify functions

Following functions trigger a gsc notify event.

#### Plugin_Scr_NotifyLevel( int strIdx, int paramNum )

Triggers a level notify event with allocated string with strIdx and number of parameters.

Usage example:
Lua:
```lua
allocatedStrings = {}

--[[ 
Called on gametype start - Each time map fully restarts or rotates
]]--
function OnSpawnServer ()

    allocatedStrings.notifyindex_clientupdate = Plugin_Scr_AllocString( "client_update" )
    -- ....
end

function doEvent ()
    Plugin_Scr_AddInt( Plugin_Milliseconds() )
    Plugin_Scr_NotifyLevel( allocatedStrings.notifyindex_clientupdate, 1 )
end
```
Gsc:
```c
init()
{
    level waittill( "client_update", time );

    // ..
}
```

#### Plugin_Scr_Notify( gentity_t *ent, int strIdx, int paramNum )

Triggers a entity notify event with allocated string with strIdx and number of parameters.

Usage example:
Lua:
```lua
allocatedStrings = {}

--[[ 
Called on gametype start - Each time map fully restarts or rotates
]]--
function OnSpawnServer ()

    allocatedStrings.notifyindex_clientupdate = Plugin_Scr_AllocString( "client_update" )
    -- ....
end

function doEvent ()
    Plugin_Scr_AddInt( Plugin_Milliseconds() )
    ent = Plugin_GetGentityForClientNum( 10 )
    Plugin_Scr_Notify( ent, allocatedStrings.notifyindex_clientupdate, 1 )
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );

    player waittill( "client_update", time )

    // ....
}
```

## ICONV functions

Can only be used when plugin is compiled with libiconv and is used to make a server-side localization.

#### Plugin_iconv_open( char *to, char *from )

Opens a conversion, returns index of open conversion.

#### Plugin_iconv_close( int conversionIndex )

Closes a conversion with convesionIndex.

#### Plugin_iconv( int conversionIndex, char *str )

Does a conversion on str, specified with open conversion at conversionIndex.

An example can be found [here](LuaScripts/examples/localization.lua)

## CVAR functions

Functions used to manipulate cvars. Cvars need to be set in config file before loading lua plugin or the value will always be default.

#### Plugin_Cvar_RegisterString( char *varName, char *varValue, int flags, char *varDesc )

Registers a string Cvar, returns reference to registered cvar. Keep the reference saved properly at all times.

Usage example:
Lua:
```lua
idkey = Plugin_Cvar_RegisterString( "http_identkey", "", 0, "Key used to authenticate POST request" )
```

#### Plugin_Cvar_RegisterBool( char *varName, qboolean varValue, int flags, char *varDesc )

Registers a boolean cvar, returns reference to registered cvar. Keep the reference saved properly at all times.

Usage example:
Lua:
```lua
usehhtp = Plugin_Cvar_RegisterBool( "http_enabled", true, 0, "Enable http functionality" )
```

#### Plugin_Cvar_RegisterInt( char *varName, int value, int minvalue, int maxvalue, int flags, char *varDesc )

Registers an integer cvar, returns reference to registered cvar. Keep the reference saved properly at all times.

Usage example:
Lua:
```lua
numplayers = Plugin_Cvar_RegisterInt( "num_players", 24, 1, 64, 0, "Maximum number of players" )
```

#### Plugin_Cvar_RegisterFloat( char *varName, float value, float minvalue, float maxvalue, int flags, char *varDesc )

Registers a float cvar, returns reference to registered cvar. Keep the reference saved properly at all times.

Usage example:
Lua:
```lua
xpmulti = Plugin_Cvar_RegisterFloat( "xpmulti", 1.5, 0.1, 10, 0, "XP multiplier" )
```

#### Plugin_Cvar_SetString( CONVAR_T *cvar, char *value )

Sets boolean value to specified cvar. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
idkey = Plugin_Cvar_RegisterString( "http_identkey", "", 0, "Key used to authenticate POST request" )

Plugin_Cvar_SetString( idkey, "123456789" )
```

#### Plugin_Cvar_SetBool( CONVAR_T *cvar, qboolean value )

Sets string value to specified cvar. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
usehhtp = Plugin_Cvar_RegisterBool( "http_enabled", true, 0, "Enable http functionality" )

Plugin_Cvar_SetBool( usehttp, false )
```

#### Plugin_Cvar_SetInt( CONVAR_T *cvar, int value )

Sets integer value to specified cvar. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
numplayers = Plugin_Cvar_RegisterInt( "num_players", 24, 1, 64, 0, "Maximum number of players" )

Plugin_Cvar_SetInt( numplayers, 48 )
```

#### Plugin_Cvar_SetFloat( CONVAR_T *cvar, float value )

Sets float value to specified cvar. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
xpmulti = Plugin_Cvar_RegisterFloat( "xpmulti", 1.5, 0.1, 10, 0, "XP multiplier" )

Plugin_Cvar_SetFloat( xpmulti, 2.5 )
```

#### Plugin_Cvar_GetString( CONVAR_T *cvar )

Returns string value of specified cvar with CONVAR_T* reference. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
idkey = Plugin_Cvar_RegisterString( "http_identkey", "", 0, "Key used to authenticate POST request" )

str = Plugin_Cvar_GetString( idkey )
```

#### Plugin_Cvar_GetBool( CONVAR_T *cvar )

Returns boolean value of specified cvar with CONVAR_T* reference. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
usehhtp = Plugin_Cvar_RegisterBool( "http_enabled", true, 0, "Enable http functionality" )

bool = Plugin_Cvar_GetBool( usehttp )
```

#### Plugin_Cvar_GetInt( CONVAR_T *cvar )

Returns integer value of specified cvar with CONVAR_T* reference. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
numplayers = Plugin_Cvar_RegisterInt( "num_players", 24, 1, 64, 0, "Maximum number of players" )

num = Plugin_Cvar_GetInt( numplayers )
```

#### Plugin_Cvar_GetFloat( CONVAR_T *cvar )

Returns float value of specified cvar with CONVAR_T* reference. CONVAR_T* is the returned reference from register cvar command.

Usage example:
Lua:
```lua
xpmulti = Plugin_Cvar_RegisterFloat( "xpmulti", 1.5, 0.1, 10, 0, "XP multiplier" )

num = Plugin_Cvar_GetFloat( xpmulti )
```

#### Plugin_Cvar_VariableStringBuffer( char *varName )

Returns string value of cvar with varName.

Usage example:
Lua:
```lua
str = Plugin_Cvar_VariableStringBuffer( "idkey" )
```

#### Plugin_Cvar_VariableValue( char *varName )

Returns float value of cvar with varName.

Usage example:
Lua:
```lua
num = Plugin_Cvar_VariableValue( "xpmulti" )
```

#### Plugin_Cvar_VariableIntegerValue( char *varName )

Returns integer value of cvar with varName.

Usage example:
Lua:
```lua
num = Plugin_Cvar_VariableIntegerValue( "numplayers" )
```

#### Plugin_Cvar_VariableBooleanValue( char *varName )

Returns boolean value of cvar with varName.

Usage example:
Lua:
```lua
bool = Plugin_Cvar_VariableBooleanValue( "http_enable" )
```

#### Plugin_Cvar_Set( char *varName, char *value )

Sets a cvar by name and by a string value which gets interpreted correctly depending on the cvar type.

Usage example:
Lua:
```lua
Plugin_Cvar_Set( "numplayers", "24" ) -- gets interpreted as int cvar
```

## HTTP function

Following function is used to make http requests. All backend logic is handled on C side. Cvar lua_enable_http must be set to 1 before loading Lua plugin to enable http functionality.

#### Plugin_HTTP_makeRequest( char *url, char *data, char *callback, char *method )

Creates an async http request, returns true on created request and false if request could not be created. URL must point to endpoint API to handle the request and data must be JSON encoded. Callback is function name in Lua, method is optional parameter and will default to "POST" if left empty. If request is sucessfuly created, the result will be passed to lua callback function. Result is json encoded string on success and nil on fail.
If request could not be created or there was error from the webserver, you can use OnFrame event to schedule another try at a later time.
Maximum number of concurent open requests is 64.


Usage example:
Lua:
```lua
function foo( gentity )

    url = "https://example.com/codapi.php"
    data = "{ 'idkey':'12345', 'action':'whatever' }"
    Plugin_HTTP_makeRequest( url, data, "cb" )
end

function cb ( result )

    if result then

    -- do something with result
    -- client might disconnect in meanwhile so gentity might be invalid at this point
    -- for extra safety work with client nums and keep track with events

    -- call callback function in gsc
    end
end
```
Gsc:
```c
init()
{
    level waittill( "connected", player );
    player foo( ::callback );
}

callback( arg1, arg2 )
{
    // ...
}
```

## MySQL functions

Enables connecting and querying of MySQL/MariaDB databases. Cvar lua_enable_mysql must be set to 1 to enable MySQL functionality. You can connect up to a maximum of 4 databases.

#### Plugin_Mysql_Connect( char *host, char *user, char *password, char *db, [int port] )

Connects to a database, port is optional and defaults to 3306. Returns database handle on success and nil on failure. This function is blocking!

Usage example:
Lua:
```lua
handle = Plugin_Mysql_Connect( "localhost", "user", "password", "database" )
```

#### Plugin_Mysql_Query( int handle, char *callback, char *query )

Starts a query with valid handle returned by Plugin_Mysql_Connect(). Returns nil if query failed to start and 1 if it started, however it can still fail later. On successfull start callback function is started with table as parameter:
.status = ErrNo ( 0 is successfull query )
.num_rows = number of rows returned for query
.affected_rows = number of affected rows for query - if query is SELECT ... it will be same as .num_rows
.num_fields = number of fields/columns returned for query

If number of returned rows is greater than 0 then results are available at row index (starting at 1) with field/column names as defined in database.
Additional cvar lua_mysql_stringnil is used to control return of NULL fields. By default if mysql field is NULL, the table field will not be created. Setting the cvar to 1 will return table field with string value "nil" instead.
This function is non-blocking!

Usage example:
Lua:
```lua
handle = Plugin_Mysql_Connect( "localhost", "user", "password", "database" )

if handle then
    Plugin_Mysql_Query( handle, "cb", "SELECT * FROM `players` WHERE `fps` = 0 LIMIT 5" )
end

function cb ( result )

    Plugin_Printf( "Status: " .. result.status .. "\n" )
    Plugin_Printf( "num_rows: " .. result.num_rows .. "\n" )
    Plugin_Printf( "affected_rows: " .. result.affected_rows .. "\n" )
    Plugin_Printf( "num_fields: " .. result.num_fields .. "\n" )

    for i=1,result.num_rows,1 do
        Plugin_Printf( "emblem: " .. result[ i ].emblem .. "\n" )
        Plugin_Printf( "id: " .. result[ i ].id .. "\n" )
    end
end
```

#### Plugin_Mysql_Close( int handle )

Closes open database connection. Function will block while there are open queries.

Usage example:
Lua:
```lua
handle = Plugin_Mysql_Connect( "localhost", "user", "password", "database" )

if handle then
    Plugin_Mysql_Close( handle )
end
```