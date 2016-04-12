next={}
function bound_check(i,j)
	if((i>=0 and j>=0)and(i<=8 and j<=9))then
		return true
	end	
	return false
end
function cannon_move(x,y,dx,dy,player)
	local i=x+dx
	local j=y+dy*player
	while(bound_check(i,j))do
		type=get_board(i,j) --if no piece type==0,player1's piece==+x,player2's piece==-x
		
		if (type~=0) then
			i=i+dx
			j=j+dy*player
			while(bound_check(i,j)) do
				type=get_board(i,j)

				if (type~=0)then
					if(type*player<0)then
						table.insert(next,i)
						table.insert(next,j)
					end
					break
				end
				
				i=i+dx
				j=j+dy*player
			end
			break 
		end
		
		table.insert(next,i)
		table.insert(next,j)
		
		
		i=i+dx
		j=j+dy*player --reverse for player 2
	end
end

function next_step(x,y,player,board)  
	next={}
	cannon_move(x,y,1,0,player)
	cannon_move(x,y,-1,0,player)
	cannon_move(x,y,0,1,player)
	cannon_move(x,y,0,-1,player)
	return next
end 

