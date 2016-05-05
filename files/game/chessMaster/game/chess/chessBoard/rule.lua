function check_result()
	winner=find_board(1);--0=no result,no player win yet,i==1 if player1 win,i==-1 if player2 win
	winner=winner-find_board(-1);
	--winner=get_chess_num_delta(1);
	return winner
end