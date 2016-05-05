#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/game/chessMaster/chessboard/renju/piece/Stone.h"
#include "class/game/chessMaster/chessboard/renju/RenjuRule.h"
namespace CM {

Renju::Renju() {
	dir_path="files/game/chessMaster/game/renju/";
	game_name="Renju";
	init_drawobject();

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=21;

	tex_path="renju/board_textures";
	normal_path="renju/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new CM::RenjuRule();
	load_mct();
}
Renju::~Renju() {

}
void Renju::create_pieces(){
	pieces.push_back(new Stone());
}
} /* namespace CM */
