local astar = require ( "astar" )

Plugin_ScrAddFunction ( "AStarSearch" )
Plugin_ScrAddFunction ( "loadWaypoints_Internal" )
Plugin_ScrAddFunction ( "getNearestWp" )
Plugin_AddCommand ( "cache_debug", 0 )

function getNearestWp ()

	local vec3 = Plugin_Scr_GetVector ( 0 )
	local nearestNode = astar.getNearestWp ( vec3 )
	Plugin_Scr_AddInt ( nearestNode - 1 )
end

function AStarSearch ()

	local start = Plugin_Scr_GetInt ( 0 )
	local goal = Plugin_Scr_GetInt ( 1 )
	local result = astar.path ( start + 1, goal + 1 )
	if not result then
		result = 1
		Plugin_Scr_Error ( "AStarSearch: Unable to find path" )
	end
	result = result - 1
	Plugin_Scr_AddInt ( result )
end

function loadWaypoints_Internal ()

	local path = Plugin_Scr_GetString ( 0 )
	local status = astar.loadWaypoints ( path )
	
	if not status then
		Plugin_Scr_Error ( "loadWaypoints_Internal: Unable to load waypoint csv" )
	end
end

function cache_debug ()

	local num = astar.cacheDebug ()
	Plugin_Printf ( "There are " .. num .. " cached paths\n" )
end