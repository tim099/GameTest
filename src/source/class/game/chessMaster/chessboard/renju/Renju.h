#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RENJU_RENJU_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include <cmath>
namespace CM {

class Renju: public ChessBoard {
	static const int MAX=10000000;
public:
	Renju();
	virtual ~Renju();
	void create_pieces();
	inline void get_pattern(int &len,int &air,int &back_air,
			int len_num[2][6]){
		//std::cout<<"get_pattern len="<<len<<"air="<<air<<"back air="<<back_air<<std::endl;
		bool p1=true;
		if(len<0){
			len=-len;
			p1=false;
		}
		int val=len;

		if(air+len+back_air<5){
			val=0;
		}else{
			if(air&&back_air)val++;
		}
		val--;
		if(val>5)val=5;
		if(val<0)val=0;
		len_num[p1?0:1][val]++;

		air=back_air;
		back_air=0;
		len=0;
	}
	inline void operate(int &type,int &len,int &air,int &back_air,
			int &total_score,int len_num[2][6]){
		if(type!=0){
			if(type*len<0){
				get_pattern(len,air,back_air,len_num);
			}else if(type*len>0&&back_air){//separated!!
				get_pattern(len,air,back_air,len_num);
			}
			len+=type;
		}else{
			if(len){//already find stone ahead
				back_air++;
			}else{
				air++;
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
		int air,back_air;
		for(int i=0;i<9;i++){
			len=0;air=0;back_air=0;
			for(int j=0;j<9;j++){
				type=chess_board->get(i,j);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)get_pattern(len,air,back_air,len_num);

			len=0;air=0;back_air=0;
			for(int j=0;j<9;j++){
				type=chess_board->get(j,i);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)get_pattern(len,air,back_air,len_num);
		}

		for(int i=0;i<5;i++){
			len=0;air=0;back_air=0;
			for(int j=0;j<9-i;j++){
				type=chess_board->get(i+j,8-j);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)if(len!=0)get_pattern(len,air,back_air,len_num);

			len=0;air=0;back_air=0;
			for(int j=0;j<9-i;j++){
				type=chess_board->get(i+j,j);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)if(len!=0)get_pattern(len,air,back_air,len_num);
		}

		for(int i=4;i<8;i++){
			len=0;air=0;back_air=0;
			for(int j=0;j<=i;j++){
				type=chess_board->get(i-j,j);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)if(len!=0)get_pattern(len,air,back_air,len_num);

			len=0;air=0;back_air=0;
			for(int j=0;j<=i;j++){
				type=chess_board->get(i-j,8-j);
				operate(type,len,air,back_air,total_score,len_num);
			}
			if(len!=0)if(len!=0)get_pattern(len,air,back_air,len_num);

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
