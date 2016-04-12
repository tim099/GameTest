next={}

function bound_check(i,j)
	if(i>=0 and j>=0 and i<8 and j<8)then
		return true
	end	
	return false
end
function next_step(x,y,player)  
	next={}
	local i
	local j
	

	if((player==1 and y==0)or(player==-1 and y==7))and(x==3)
	then
		if(get_board(4,y)==0 and get_board(5,y)==0 
		and get_board(6,y)==0 and get_board(7,y)==5*player)
		then
				table.insert(next,-1)
				table.insert(next,4)
				
				table.insert(next,3)
				table.insert(next,y)
				table.insert(next,0)
				table.insert(next,-1)
				
				table.insert(next,5)
				table.insert(next,y)
				table.insert(next,1*player)
				table.insert(next,1) --can be selected
				
				table.insert(next,7)
				table.insert(next,y)
				table.insert(next,0)
				table.insert(next,-1)
				
				table.insert(next,4)
				table.insert(next,y)
				table.insert(next,5*player)
				table.insert(next,-1)			
		end
		if(get_board(2,y)==0 and get_board(1,y)==0 
		and get_board(0,y)==5*player)
		then
				table.insert(next,-1)
				table.insert(next,4)
				
				table.insert(next,3)
				table.insert(next,y)
				table.insert(next,0)
				table.insert(next,-1)
				
				table.insert(next,1)
				table.insert(next,y)
				table.insert(next,1*player)
				table.insert(next,1) --can be selected
				
				table.insert(next,0)
				table.insert(next,y)
				table.insert(next,0)
				table.insert(next,-1)
				
				table.insert(next,2)
				table.insert(next,y)
				table.insert(next,5*player)
				table.insert(next,-1)		
		
		end
	end
	
	
	i=x
	j=y+1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x
	j=y-1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y+1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y+1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x+1
	j=y-1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end
	
	i=x-1
	j=y-1*player
	if bound_check(i,j)
	and get_board(i,j)*player<=0 then
		table.insert(next,i)
		table.insert(next,j)
	end	
	return next
end 

