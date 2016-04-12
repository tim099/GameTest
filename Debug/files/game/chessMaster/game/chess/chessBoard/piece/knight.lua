next={}

function bound_check(i,j)
	if(i>=0 and j>=0 and i<8 and j<8)then
		return true
	end	
	return false
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
				table.insert(next,4*player)
				table.insert(next,0)
			end
		end
		return next
	end
	
	local i=x+1
	local j=y+2*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y-2*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y+2*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y-2*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
--
	i=x+2
	j=y+1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+2
	j=y-1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-2
	j=y+1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-2
	j=y-1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end

	return next
end 
