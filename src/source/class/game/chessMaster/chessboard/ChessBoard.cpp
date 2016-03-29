#include "class/game/chessMaster/chessboard/ChessBoard.h"

namespace CM {

ChessBoard::ChessBoard(int sizex,int sizey,int sizez) {
	board=new Tim::Array3D<unsigned char>(sizex,sizey,sizez);
	init();
}
ChessBoard::~ChessBoard() {
	delete board;
}
void ChessBoard::init(){
	for(int i=0;i<board->sizex;i++){
		for(int j=0;j<board->sizey;j++){
			for(int k=0;k<board->sizez;k++){
				if(j==0){
					board->get(i,j,k)=1;//button of the board
				}else{
					board->get(i,j,k)=0;
				}
			}
		}
	}
}
} /* namespace CM */
