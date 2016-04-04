str2 = "I am so cool"  
str = "I am tim" 
str3 = "I am marry"  
t = test(4)
print("t is ", t)  

function test() return 1,2 end
function test2() return test() end
function test3()
    local values = {test2()}
    table.insert(values,3)
    return unpack(values)
end

print(test3())

function next_step(x,y)  
	step_num=0;
	local next={}
	
	table.insert(next,x)
	table.insert(next,y+1)
	step_num=step_num+1;
	
	table.insert(next,x)
	table.insert(next,y-1)
	step_num=step_num+1;
	
	table.insert(next,x+1)
	table.insert(next,y)
	step_num=step_num+1;
	
	table.insert(next,x-1)
	table.insert(next,y)
	step_num=step_num+1;
	
	return next,step_num
end  

next,step_num=next_step(1,2)
print("step_num=",step_num)
for i=1,step_num do
	print(next[2*i-1],next[2*i])
end
print(unpack(next))