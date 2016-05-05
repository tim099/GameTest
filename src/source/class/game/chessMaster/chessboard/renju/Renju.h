#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include <cmath>
namespace CM {

class Renju: public ChessBoard {
	static const int MAX=10000000;
public:
	static const int board_size=9;
	Renju();
	virtual ~Renju();
	void create_pieces();
	inline void get_pattern(int &len,int &space,int &back_space,
			int len_num[2][6]){
		//std::cout<<"get_pattern len="<<len<<"air="<<air<<"back air="<<back_air<<std::endl;
		bool p1=true;
		if(len<0){
			len=-len;
			p1=false;
		}
		if(space+len+back_space<5){
			len=0;
		}else{
			if(space&&back_space)len++;
		}
		len--;
		if(len>5)len=5;
		if(len<0)len=0;
		len_num[p1?0:1][len]++;

		space=back_space;
		back_space=0;
		len=0;
	}
	inline void operate(int &type,int &len,int &space,int &back_space,
			int &total_score,int len_num[2][6]){
		if(type!=0){
			if(type*len<0){
				get_pattern(len,space,back_space,len_num);
			}else if(type*len>0&&back_space){//separated!!
				get_pattern(len,space,back_space,len_num);
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
		int len_num[2][6];
		for(int i=0;i<6;i++){
			len_num[0][i]=0;
			len_num[1][i]=0;
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

		for(int i=0;i<=(board_size-5);i++){
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

		for(int i=4;i<board_size-1;i++){
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

		if(player==1){
			for(int i=4;i>0;i--){
				if(len_num[0][i]>0){
					//std::cout<<"p1 find:"<<i<<std::endl;
					len_num[0][i]-=2;
					len_num[0][i+1]++;
					break;
				}
			}
		}else{
			for(int i=4;i>0;i--){
				if(len_num[1][i]>0){
					len_num[1][i]-=2;
					len_num[1][i+1]++;
					break;
				}
			}
		}
		for(int i=0;i<6;i++){
			if(i==3){
				if(len_num[0][i]>=2){
					len_num[0][i]-=3;
					len_num[0][i+1]++;
				}
				if(len_num[1][i]>=2){
					len_num[1][i]-=3;
					len_num[1][i+1]++;
				}
				total_score+=100*(len_num[0][i]-len_num[1][i]);
			}else if(i==4){
				total_score+=1000*(len_num[0][i]-len_num[1][i]);
			}else if(i>=5){
				total_score+=10000*(len_num[0][i]-len_num[1][i]);
			}else{
				total_score+=(i+1)*(i+1)*(len_num[0][i]-len_num[1][i]);
			}

		}
		return player*total_score;
	}
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_ */
