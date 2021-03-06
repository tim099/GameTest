next={}
function bound_check(i,j)
	if((i>=0 and j>=0)and(i<=8 and j<=9))then
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

function next_step(x,y,player,board)  
	next={}
	move_straight(x,y,1,0,player)
	move_straight(x,y,-1,0,player)
	move_straight(x,y,0,1,player)
	move_straight(x,y,0,-1,player)
	return next
end 
