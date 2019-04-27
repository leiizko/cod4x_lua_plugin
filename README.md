# Call of Duty 4 X Lua Plugin
This plugin adds support for CoD4X plugins written in Lua. It is suited towards modders, who require faster functions to be used within gsc scripts and do not want to deal with writting a C plugin. Functions written in Lua are up to 10 times faster than in gsc.

# Usage
All usable function are listed [here](https://github.com/leiizko/cod4x_lua_plugin/blob/master/main.c#L45). All functions have same usage parameters as stock plugin function with exception of:
```
Plugin_AddCommand( (string)<function name>, (int)<power> )
Plugin_ScrAddFunction( (string)<function name> )
vec = Plugin_Scr_GetVector( (int)<param number> )
```
* function name is both name of function in gsc and in lua.
* power is the power needed to run the command, 0 is rcon only, 1 is for everyone.
* param number is the index of parameter passed within gsc, starting at 0.

Extra notes about vectors in Lua:
* Vector is a table with size of 3
* Index must always start at 1 ( vec[1], vec[2], vec[3] )
* You can simply define the vector as `vec = { 192.27, 946.5, 2895.99 }`

Lua scripts must be placed in server homepath and loaded with "lua_loadscript <script path>" command

## Example
server.cfg:
```
loadplugin lua
lua_loadscript "lua_scripts/test.lua" // script is located in fs_homepath/lua_scripts
```
test.lua:
```
Plugin_ScrAddFunction( "mysqrt" )

function mysqrt ()
    local n = Plugin_Scr_GetFloat( 0 ) --get number (float) from gsc
    local x0 = n
    local x1 = 0
    local delta
    while ( 1 )
    do
        x1 = x0 - (x0*x0 - n)/(2*x0)
        delta = (x1-x0)/x0;
        if ( delta < 0.000001 and delta > -0.000001 ) then
            break
        end
        x0 = x1
    end
    Plugin_Scr_AddFloat( x1 ) --add result (float) to gsc
end
```
gsc:
```
main()
{
    num = 123;
    print( "Square root of " + num + " is " + mysqrt( num ) + "\n" );
}
```

# Compiling
Enter directory and run make. Needs to be placed in plugins directory in CoD4X server source code. On Windows you need to compile the server first.
