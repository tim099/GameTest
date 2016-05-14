#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include <cmath>
namespace CM {

class Renju: public ChessBoard {
	static const int MAX=10000000;
public:
	static const int board_size=9;
	static const int win_length=5;
	//static const int arr_size=win_lenth+1;
	Renju();
	virtual ~Renju();
	void create_pieces();
	inline void get_pattern(int &len,int &space,int &back_space,
			int len_num[4][win_length]){
		//std::cout<<"get_pattern len="<<len<<"air="<<air<<"back air="<<back_air<<std::endl;
		bool p1=true;
		bool alive=false;
		if(len<0){
			len=-len;
			p1=false;
		}
		if(space+len+back_space<win_length){
			len=0;//can't form win length
		}else{
			if(space&&back_space){
				alive=true;
			}
		}
		len--;
		if(len>=win_length)len=win_length-1;
		if(len<0)len=0;
		len_num[(p1?0:1)+(alive?2:0)][len]++;
		space=back_space;
		back_space=0;
		len=0;
	}
	inline void operate(int &type,int &len,int &space,int &back_space,
			int &total_score,int len_num[4][win_length]){
		if(type!=0){
			if(type*len<0){
				get_pattern(len,space,back_space,len_num);
			}else if(type*len>0&&back_space){//separated!!
				if(back_space>1){
					get_pattern(len,space,back_space,len_num);
				}else{
					 if(type*len>1){
						 if(type*len==2){
							 len+=type;
							 len_num[type>0?0:1][1]--;
						 }
						 get_pattern(len,space,back_space,len_num);
					 }
				}

			}
			len+=type;
		}else{
			if(len){//already find stone ahead
				back_space++;
			}else{
				space++;
			}
		}
	}
	virtual int evaluate_score(CM::Board<short int> *chess_board,int player){
		//std::cout<<"==============="<<std::endl;
		int total_score=0;
		int len,type;
		int len_num[4][win_length];
		for(int i=0;i<win_length;i++){
			len_num[0][i]=0;
			len_num[1][i]=0;
			len_num[2][i]=0;
			len_num[3][i]=0;
		}
		int space,back_space;
		for(int i=0;i<board_size;i++){
			len=0;space=0;back_space=0;
			for(int j=0;j<board_size;j++){
				type=chess_board->get(i,j);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);

			len=0;space=0;back_space=0;
			for(int j=0;j<board_size;j++){
				type=chess_board->get(j,i);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);
		}

		for(int i=0;i<=(board_size-win_length);i++){
			len=0;space=0;back_space=0;
			for(int j=0;j<board_size-i;j++){
				type=chess_board->get(i+j,board_size-j-1);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);

			len=0;space=0;back_space=0;
			for(int j=0;j<board_size-i;j++){
				type=chess_board->get(i+j,j);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);
		}

		for(int i=(win_length-1);i<board_size-1;i++){
			len=0;space=0;back_space=0;
			for(int j=0;j<=i;j++){
				type=chess_board->get(i-j,j);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);

			len=0;space=0;back_space=0;
			for(int j=0;j<=i;j++){
				type=chess_board->get(i-j,board_size-j-1);
				operate(type,len,space,back_space,total_score,len_num);
			}
			if(len!=0)get_pattern(len,space,back_space,len_num);
		}
		///*
		if(player==1){
			for(int i=win_length-1;i>0;i--){
				if(len_num[2][i]>0){
					len_num[2][i]-=4;//alive
					len_num[2][i+1]++;
					break;
				}
				if(len_num[0][i]>0){
					len_num[0][i]-=4;//dead
					len_num[0][i+1]++;
					break;
				}
			}
		}else{
			for(int i=win_length-1;i>0;i--){
				if(len_num[3][i]>0){
					len_num[3][i]-=4;//alive
					len_num[3][i+1]++;
					break;
				}
				if(len_num[1][i]>0){
					len_num[1][i]-=4;//dead
					len_num[1][i+1]++;
					break;
				}
			}
		}
		//*/
		for(int i=0;i<win_length;i++){
			//std::cout<<"b"<<i+1<<","<<len_num[0][i]<<","<<len_num[2][i]<<std::endl;
			//std::cout<<"w"<<i+1<<","<<len_num[1][i]<<","<<len_num[3][i]<<std::endl;
			///*
			if(i==win_length-2||i==win_length-3){
				if (len_num[0][i] >= 2) {
					len_num[0][i] -= 6;
					len_num[0][i+1]++;
				}
				if (len_num[1][i] >= 2) {
					len_num[1][i] -= 6;
					len_num[1][i+1]++;
				}
				if(len_num[2][i]>=1&&len_num[0][i+1]>=1){
					len_num[2][i]--;
					len_num[0][i+1]--;
					len_num[2][i+1]++;
					//std::cout<<"p1 d4a3!!"<<std::endl;
				}else if(len_num[2][i]>=2) {
					//std::cout<<"p1 2a3!!"<<std::endl;
					len_num[2][i]-=6;
					len_num[2][i+1]++;
				}
				if(len_num[3][i]>=1&&len_num[1][i+1]>=1){
					len_num[3][i]--;
					len_num[1][i+1]--;
					len_num[3][i+1]++;
					//std::cout<<"p2 d4a3!!"<<std::endl;
				}else if(len_num[3][i]>=2) {
					len_num[3][i]-=6;
					len_num[3][i+1]++;
					//std::cout<<"p2 2a3!!"<<std::endl;
				}
			}
			//*/
			total_score+=pow(10,i)*(len_num[0][i]-len_num[1][i]);
			total_score+=5*pow(10,i)*(len_num[2][i]-len_num[3][i]);
		}
		return player*total_score;
	}
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_ */
