# Call of Duty 4 X Lua Plugin
This plugin adds support for CoD4X plugins written in Lua, removing any need to compile it against CoD4X server enabling rapid development. It is best used to replace expensive gsc functions and to add additional functionality to game with persistent storage and http capability. Using libiconv it can also serve as server side localization option.

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

Function documentation can be found [here](functiondoc.md).
Event documentation can be found [here](LuaScripts/examples/events.lua)

# Compiling
To compile without libiconv enter directory and run make. To include libiconv enter directory and run make ICONV=TRUE. 
On Windows you need to compile the server first.