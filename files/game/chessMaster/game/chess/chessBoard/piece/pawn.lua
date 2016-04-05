next={}

function next_step(x,y,player)  
	next={}
	i=x
	j=y+1*player
	if (bound_check(i,j)~=0) 
	and (get_board(i,j)==0) then
		table.insert(next,i)
		table.insert(next,j)
		
		i=x
		j=y+2*player --move two step if this is the first step
		if((player==1 and y==1)or(player==-1 and y==6))
		and (get_board(i,j)==0)then
			table.insert(next,i)
			table.insert(next,j)
		end
	end

	
	i=x+1
	j=y+1*player --attack step
	
	if (bound_check(i,j)~=0) 
	and (get_board(i,j)*player<0) then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y+1*player --attack step
	
	if (bound_check(i,j)~=0) 
	and (get_board(i,j)*player<0) then
		table.insert(next,i)
		table.insert(next,j)
	end		
	
	return next
end 