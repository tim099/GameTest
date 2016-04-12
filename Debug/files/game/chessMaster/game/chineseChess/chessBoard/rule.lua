function check_result()
	winner=0 --no result,no player win yet,i==1 if player1 win,i==-1 if player2 win
	for i=3,5 do
		for j=0,9 do
			local type=get_board(i,j)
			if(type==1)then --player1's king==1
				winner=winner+1
			end
			if(type==-1)then --player2's king==-1
				winner=winner-1
			end
		end
	end

	return winner
end