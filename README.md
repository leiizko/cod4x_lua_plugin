# Call of Duty 4 X Lua Plugin [![build](https://github.com/leiizko/cod4x_lua_plugin/actions/workflows/build.yml/badge.svg)](https://github.com/leiizko/cod4x_lua_plugin/actions/workflows/build.yml)
This plugin adds support for CoD4X plugins written in Lua, removing any need to compile it against CoD4X server enabling rapid development. It is best used to replace expensive gsc functions and to add additional functionality to game with persistent storage, HTTP and MySQL connectivity and encoding support with libiconv for server side localization posibility.

# Usage
To begin using the plugin first load it from a server config or command line with:
```
loadplugin lua
```
Create an entry lua script and load it after starting the plugin in server config or command line with:
```
lua_loadscript "path/script.lua"
```
Do not load more than 1 script via this command, use entry lua script to load any additional scripts.

To enable HTTP functionality set cvar lua_enable_http to 1 and to enable MySQL functionality set cvar lua_enable_mysql to 1 **BEFORE** loading the plugin.

Function documentation can be found [here](functiondoc.md#function-reference).
Event documentation can be found [here](LuaScripts/examples/events.lua)

As of version 0.5 plugin requires server version [b3b68dd](https://github.com/callofduty4x/CoD4x_Server/commit/b3b68dda2ede9c83c28192ac8973b9bb19265599) or later.

# Compiling
Get server source first [here](https://github.com/callofduty4x/CoD4x_Server). Place plugin source into plugins/lua within server source, enter lua directory and run make. Compiled binary will be placed in bin directory.

On Windows OS server must be compiled first.
