-- ======================================================================
-- Copyright (c) 2012 RapidFire Studio Limited 
-- All Rights Reserved. 
-- http://www.rapidfirestudio.com

-- Permission is hereby granted, free of charge, to any person obtaining
-- a copy of this software and associated documentation files (the
-- "Software"), to deal in the Software without restriction, including
-- without limitation the rights to use, copy, modify, merge, publish,
-- distribute, sublicense, and/or sell copies of the Software, and to
-- permit persons to whom the Software is furnished to do so, subject to
-- the following conditions:

-- The above copyright notice and this permission notice shall be
-- included in all copies or substantial portions of the Software.

-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
-- EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
-- MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
-- IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
-- CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
-- TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
-- SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-- ======================================================================

local astar = {}

----------------------------------------------------------------
-- local variables
----------------------------------------------------------------

local INF = 1/0
local cachedPaths = {}
local nodes = nil
local cachedNum = 0

----------------------------------------------------------------
-- local functions
----------------------------------------------------------------

local function VectorLengthSquared ( vec3 )

	return math.pow( vec3 [ 1 ], 2 ) +  math.pow( vec3 [ 2 ], 2 ) +  math.pow( vec3 [ 3 ], 2 )
end

local function VectorSubtract ( v1, v2 )

	local vec3 = {}
	vec3 [ 1 ] = v1 [ 1 ] - v2 [ 1 ]
	vec3 [ 2 ] = v1 [ 2 ] - v2 [ 2 ]
	vec3 [ 3 ] = v1 [ 3 ] - v2 [ 3 ]
	return vec3
end

local function Vec3DistanceSq ( v1, v2 )

	local vec3 = VectorSubtract ( v1, v2 )
	return VectorLengthSquared ( vec3 )
end

local function dist_between ( nodeA, nodeB )

	return Vec3DistanceSq ( nodeA.origin, nodeB.origin )
end

local function heuristic_cost_estimate ( nodeA, nodeB )

	return Vec3DistanceSq ( nodeA.origin, nodeB.origin )
end

local function lowest_f_score ( set, f_score )

	local lowest, bestNode = INF, nil
	for _, node in ipairs ( set ) do
		local score = f_score [ node ]
		if score < lowest then
			lowest, bestNode = score, node
		end
	end
	return bestNode
end


local function neighbor_nodes ( theNode )

	local neighbors = {}
	for _, nodenum in ipairs ( theNode.children ) do
			table.insert ( neighbors, nodes [ nodenum ] )
	end
	return neighbors
end

local function not_in ( set, theNode )

	for _, node in ipairs ( set ) do
		if node == theNode then return false end
	end
	return true
end

local function remove_node ( set, theNode )

	for i, node in ipairs ( set ) do
		if node == theNode then 
			set [ i ] = set [ #set ]
			set [ #set ] = nil
			break
		end
	end	
end

local function unwind_path ( flat_path, map, current_node )

	if map [ current_node ] then
		table.insert ( flat_path, 1, map [ current_node ] ) 
		return unwind_path ( flat_path, map, map [ current_node ] )
	else
		return flat_path
	end
end

local function strtok ( inputstr, sep )

	local t = {}
	for str in string.gmatch ( inputstr, "([^"..sep.."]+)" ) do
		table.insert ( t, str )
	end
	return t
end

local function buildNodes ( tokens )

	local protonode = {}
	protonode.id = tonumber ( tokens[ 1 ] [ 1 ] )
	protonode.origin = {}
	protonode.children = {}
	
	for _, org in ipairs ( tokens [ 2 ] ) do
		table.insert ( protonode.origin, tonumber ( org ) )
	end
	
	for _, child in ipairs ( tokens [ 3 ] ) do
		local realchild = tonumber ( child ) + 1
		if realchild ~= protonode.id then
			table.insert ( protonode.children, realchild )
		end
	end
	
	table.insert ( nodes, protonode )
end

----------------------------------------------------------------
-- pathfinding functions
----------------------------------------------------------------

local function a_star ( start, goal )

	local closedset = {}
	local openset = { start }
	local came_from = {}

	local g_score, f_score = {}, {}
	g_score [ start ] = 0
	f_score [ start ] = heuristic_cost_estimate ( start, goal )

	while #openset > 0 do
	
		local current = lowest_f_score ( openset, f_score )
		if current == goal then
			local path = unwind_path ( {}, came_from, goal )
			table.insert ( path, goal )
			return path
		end

		remove_node ( openset, current )		
		table.insert ( closedset, current )
		
		local neighbors = neighbor_nodes ( current )
		for _, neighbor in ipairs ( neighbors ) do 
			if not_in ( closedset, neighbor ) then
			
				local tentative_g_score = g_score [ current ] + dist_between ( current, neighbor )
				 
				if not_in ( openset, neighbor ) or tentative_g_score < g_score [ neighbor ] then 
					came_from 	[ neighbor ] = current
					g_score 	[ neighbor ] = tentative_g_score
					f_score 	[ neighbor ] = g_score [ neighbor ] + heuristic_cost_estimate ( neighbor, goal )
					if not_in ( openset, neighbor ) then
						table.insert ( openset, neighbor )
					end
				end
			end
		end
	end
	return nil -- no valid path
end

----------------------------------------------------------------
-- exposed functions
----------------------------------------------------------------

function astar.cacheDebug ()

	return cachedNum
end

function astar.path ( start, goal )

	local isCached = 1
	if not cachedPaths [ start ] then
		cachedPaths [ start ] = {}
		isCached = nil
	elseif cachedPaths [ start ] [ goal ] then
		return cachedPaths [ start ] [ goal ]
	end
	
	-- Check for cached children of start node
	for _, child in ipairs ( nodes [ start ].children ) do
		if cachedPaths [ child ] and cachedPaths [ child ] [ goal ] then
			return child
		end
	end
	
	-- Check for cached children of goal node
	if isCached then 
		for _, child in ipairs ( nodes [ goal ].children ) do
			if cachedPaths [ start ] [ child ] then
				return cachedPaths [ start ] [ child ]
			end
		end
	end

	local resPath = a_star ( nodes[ start ], nodes[ goal ] )
	if not resPath then
		return nil
	end
	
	local paths = {}
	for i, node in ipairs ( resPath ) do
		table.insert ( paths, node.id )
	end
	
	for i, id in ipairs ( paths ) do
		if id == goal then
			break
		end
		
		if not cachedPaths [ id ] then
			cachedPaths [ id ] = {}
		end
		if not cachedPaths [ id ] [ goal ] then
			local n = i + 1
			cachedPaths [ id ] [ goal ] = paths [ n ] -- Cache only next node
			cachedNum = cachedNum + 1
		end
	end

	return resPath[ 2 ].id
end

function astar.getNearestWp ( origin )

	local nearestWp = -1
	local nearestDist = 99999999999
	
	for _, node in ipairs ( nodes ) do
		local dist =  Vec3DistanceSq ( origin, node.origin )
		
		if dist < nearestDist then
			nearestDist = dist
			nearestWp = node.id
		end
	end
	
	return nearestWp
end

function astar.loadWaypoints ( filename )

	nodes = {}
	cachedPaths = {}
	cachedNum = 0
	
	handle, err = io.open ( filename )
	
	if err then
		return nil
	end
	
	while true do
		local line = handle:read ()
		if not line then
			break
		end
		
		local tokens = {}
		tokens.fisttok = strtok ( line, "," )
		tokens.finaltok = {}
		
		for _, tok in ipairs ( tokens.fisttok ) do
			local ftok = strtok ( tok, "%s" )
			table.insert ( tokens.finaltok, ftok )
		end
		
		buildNodes ( tokens.finaltok )
	end
	
	return 1
end	

return astar