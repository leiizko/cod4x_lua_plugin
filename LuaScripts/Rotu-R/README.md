# RotU-R Pathfinding
This will replace GSC implementation of pathfinding with Lua one. Worse cases take up to 0.5msec to calculate, down from 160msec on GSC and after it is calcuated the path gets cached. At the moment cache is unlimited which can cause higher memory usage ( few MBytes ) but can be limited easily if needed. Access from cache, even when huge in size takes ~1usec.

# Installing:
* Place both Lua scripts into CoD4_Server_Dir/Lua
* Load rotu.lua using lua_loadscript function in your server config file
* Modify waypoints.gsc: 
	- If you are using unmodified version of RoTu-R mod, simply drop [waypoints.gsc](https://github.com/leiizko/cod4x_lua_plugin/blob/master/LuaScripts/Rotu-R/waypoints.gsc) into Mod_Dir/scripts/include folder. If it doesn't exist create one.
	- If you are using modified version make changes as shown in [this commit](https://github.com/leiizko/cod4x_lua_plugin/commit/35dde9db1fea393626eaf7c534fc7e15ca2c2ceb)
