next={}

function next_step(x,y,player)  
	next={}
	i=x+1
	j=y+2*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y-2*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y+2*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y-2*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
--
	i=x+2
	j=y+1*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+2
	j=y-1*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-2
	j=y+1*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-2
	j=y-1*player
	if bound_check(i,j)~=0 
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end

	return next
end 
