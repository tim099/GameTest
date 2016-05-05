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
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<Renju::board_size;j++){
			type=chess_board->get(j,i);
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
	}
	//================1=====================
	for(int i=0;i<5;i++){
		len=0;
		for(int j=0;j<9-i;j++){
			type=chess_board->get(i+j,8-j);
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<9-i;j++){
			type=chess_board->get(i+j,j);
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
	}

	for(int i=4;i<8;i++){
		len=0;
		for(int j=0;j<=i;j++){
			type=chess_board->get(i-j,j);
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
		len=0;
		for(int j=0;j<=i;j++){
			type=chess_board->get(i-j,8-j);
			if(type>0){
				if(len<0)len=0;
				len++;
				if(len>=5)return 1;
			}else if(type<0){
				if(len>0)len=0;
				len--;
				if(len<=-5)return -1;
			}else{
				len=0;
			}
		}
	}
	//================2=====================

	return 0;
}
} /* namespace CM */
