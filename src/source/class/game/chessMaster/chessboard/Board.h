#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARD_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARD_H_

#include "class/tim/array/Array2D.h"
#include <iostream>
namespace CM {
template <class Type>
class Board: public Tim::Array2D<Type> {
public:
	Board(int _sizex,int _sizey,int _chess_type_num) : Tim::Array2D<Type>(_sizex,_sizey){
		piece_type_num=_chess_type_num;
		piece_num=new Type[piece_type_num];
		for(int i=0;i<piece_type_num;i++){
			piece_num[i]=0;
		}
		for(int i=0;i<this->sizex;i++){
			for(int j=0;j<this->sizey;j++){
				this->get(i,j)=0;
			}
		}
		//std::cout<<"Board piece_type_num="<<piece_type_num<<std::endl;
	}
	Board(Board* board) : Tim::Array2D<Type>(board){
		piece_type_num=board->piece_type_num;
		piece_num=new Type[piece_type_num];
		for(int i=0;i<piece_type_num;i++){
			piece_num[i]=board->piece_num[i];
		}

	}
	virtual ~Board(){
		delete[] piece_num;
	}
	Type *piece_num;
	int piece_type_num;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARD_H_ */
