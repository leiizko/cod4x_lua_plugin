# RotU-R Pathfinding
This will replace GSC implementation of pathfinding with Lua one. It is up to 160 times faster on first search, generated paths get cached.

# Installing:
* Place both Lua scripts into CoD4_Server_Dir/Lua
* Load rotu.lua using lua_loadscript function in your server config file
* Modify waypoints.gsc: 
	- If you are using unmodified version of RoTu-R mod, simply drop waypoints.gsc into Mod_Dir/scripts/include folder. If it doesn't exist create one.
	- If you are using modified version make changes as shown in waypoints.diff file