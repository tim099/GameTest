#include "class/game/chessMaster/chessboard/chess/ChineseChess.h"
#include "class/game/chessMaster/chessboard/chess/piece/General.h"
#include "class/game/chessMaster/chessboard/chess/piece/Advisor.h"
#include "class/game/chessMaster/chessboard/chess/piece/Elephant.h"
#include "class/game/chessMaster/chessboard/chess/piece/Horse.h"
#include "class/game/chessMaster/chessboard/chess/piece/Chariot.h"
#include "class/game/chessMaster/chessboard/chess/piece/Cannon.h"
#include "class/game/chessMaster/chessboard/chess/piece/Soildier.h"
#include "class/game/chessMaster/chessboard/chess/ChineseChessRule.h"
namespace CM {

ChineseChess::ChineseChess() {
	dir_path="files/game/chessMaster/game/chineseChess/";
	init_drawobject();

	rule_path=dir_path+"chessBoard/rule.lua";

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=21;

	tex_path="chineseChess/board_textures";
	normal_path="chineseChess/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new CM::ChineseChessRule();
	load_mct();

	//rule->load_rule(rule_path);
}
ChineseChess::~ChineseChess() {

}
void ChineseChess::create_pieces(){
	///*
	pieces.push_back(new General());
	pieces.push_back(new Advisor());
	pieces.push_back(new Elephant());
	pieces.push_back(new Horse());
	pieces.push_back(new Chariot());
	pieces.push_back(new Cannon());
	pieces.push_back(new Soildier());
	init_pieces();
    //*/
}
} /* namespace CM */
