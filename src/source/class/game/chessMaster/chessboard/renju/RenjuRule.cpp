#include "class/game/chessMaster/chessboard/renju/RenjuRule.h"
#include "class/game/chessMaster/chessboard/renju/Renju.h"
namespace CM {

RenjuRule::RenjuRule() {

}
RenjuRule::~RenjuRule() {

}
int RenjuRule::check_winner(CM::Board<short int> *chess_board){
	int len,type;
	for(int i=0;i<Renju::board_size;i++){
		len=0;
		for(int j=0;j<Renju::board_size;j++){
			type=chess_board->get(i,j);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<Renju::board_size;j++){
			type=chess_board->get(j,i);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
	}

	for(int i=0;i<=(Renju::board_size-Renju::win_length);i++){
		len=0;
		for(int j=0;j<Renju::board_size-i;j++){
			type=chess_board->get(i+j,Renju::board_size-j-1);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<Renju::board_size-i;j++){
			type=chess_board->get(i+j,j);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
	}

	for(int i=Renju::win_length-1;i<Renju::board_size-1;i++){
		len=0;
		for(int j=0;j<=i;j++){
			type=chess_board->get(i-j,j);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<=i;j++){
			type=chess_board->get(i-j,Renju::board_size-j-1);
			if(type!=0){
				if(len*type<0)len=0;
				len+=type;
				if(len*type>=Renju::win_length)return type;
			}else{
				len=0;
			}
		}
	}
	//================2=====================

	return 0;
}
} /* namespace CM */
