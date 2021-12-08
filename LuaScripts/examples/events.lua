-- Events called by server->plugin --

--[[ 
Called when player gets banned
playerid == HWID of banned player
steamid == SteamID of banned player if one exists
adminsteamid == SteamID of admin that invoked the ban
]]--
function OnPlayerAddBan ( playerid, steamid, adminsteamid )

end

--[[ 
Called when player disconnects for any reason
clientid == player slot number
]]--
function OnPlayerDC ( clientid, playerid, steamid )

end

-- Called every frame == 50msec
function OnFrame ()

end

--[[ 
Called when player completes auth - used as completed client connect
rejectmsg == if exists player got dropped in meantime
]]--
function OnPlayerGotAuthInfo ( clientid, playerid, steamid, rejectmsg )

end

--[[ 
Called on gametype start - Each time map fully restarts or rotates
]]--
function OnSpawnServer ()

end

--[[ 
Called after map fast restarts
]]--
function OnPostFastRestart ()

end

--[[ 
Called when map ends
]]--
function OnExitLevel ()

end

--[[ 
Called when a player writes a message
message = what player wrote
slot = slot number of player who wrote the message
show = show the message? true-show; false-hide
mode = 0 == all chat, 1 == team chat
]]--
function OnMessageSent( message, slot, show, mode )

    return show
end