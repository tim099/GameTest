next={}

function bound_check(i,j)
	if(i>=0 and j>=0 and i<8 and j<8)then
		return true
	end	
	return false
end
function move_straight(x,y,dx,dy,player)
	local i=x+dx
	local j=y+dy*player
	while(bound_check(i,j))do
		type=get_board(i,j) --if no piece type==0,player1's piece==+x,player2's piece==-x
		
		if type*player>0 then break end --stop by player's own piece
		table.insert(next,i)
		table.insert(next,j)
		
		if type*player<0 then break end --attack enemy and stop here
		
		i=i+dx
		j=j+dy*player --reverse for player 2
	end
end

function next_step(x,y,player)  
	next={}
	if(not bound_check(x,y))then
		local i
		local j
		if(player==-1)then j=0 else j=7 end
		
		for i=0,7 do
			type=get_board(i,j)
			if(type*player==6)then
				table.insert(next,-1)
				table.insert(next,1)
				table.insert(next,i)
				table.insert(next,j)
				table.insert(next,3*player)
				table.insert(next,0)
			end
		end
		return next
	end
	move_straight(x,y,1,1,player)
	move_straight(x,y,-1,1,player)
	move_straight(x,y,1,-1,player)
	move_straight(x,y,-1,-1,player)
	return next
end 