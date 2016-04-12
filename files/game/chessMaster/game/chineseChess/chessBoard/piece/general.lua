next={}
function bound_check(i,j)
	if((i>=0 and j>=0)and(i<=8 and j<=9))then
		return true
	end	
	return false
end
function in_nine(x,y)
	if ((x>=3) and (x<=5)) then
		if((y>=0) and (y<=2))
		or((y>=7) and (y<=9))
		then
			return true	
		end	
	end

	return false
end

function see_general(x,y,player)
	local i=x
	local j=y+player
	while(bound_check(i,j))do
		
		type=get_board(i,j) --if no piece type==0,player1's piece==+x,player2's piece==-x

		if type~=0 then
			if(type==-player)then
				table.insert(next,i)
				table.insert(next,j)
			end 
			break 
		end 
		j=j+player
	end
end

function next_step(x,y,player,board)  
	next={}
	see_general(x,y,player)
	i=x
	j=y+1*player
	if bound_check(i,j)
	and in_nine(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x
	j=y-1*player
	if bound_check(i,j)
	and in_nine(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y
	if bound_check(i,j)
	and in_nine(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y
	if bound_check(i,j)
	and in_nine(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	return next
end 

