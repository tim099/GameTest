#include "class/game/chessMaster/chessboard/Rule.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Rule::Rule() {
	rule=0;
	rule_mutex=new Tim::Mutex();
}
Rule::~Rule() {
	if(rule)delete rule;
	delete rule_mutex;
}
void Rule::load_rule(std::string path){
	if(rule)delete rule;
	rule=new Tim::Lua();
	rule->loadfile(path);
	//rule->rigister_function("bound_check",ChessBoard::bound_check);
	rule->rigister_function("get_board",ChessBoard::get_board);
	rule->rigister_function("find_board",ChessBoard::find_board);
	rule->rigister_function("get_chess_num_delta",ChessBoard::get_chess_num_delta);
	rule->p_call(0,0,0);
}
int Rule::check_winner(CM::Board<short int> *chess_board){
	rule_mutex->wait_for_this();
	rule->pushlightuserdata(chess_board);
	rule->set_global("board");
	//ChessBoard::get_cur_object()->set_current(chess_board);

	rule->get_global("check_result");
	rule->p_call(0,1,0);
	int result=rule->get_number(-1);
	//std::cout<<"ChessBoard::check_winner() result="<<result<<std::endl;

	rule_mutex->release();
	return result;
}
} /* namespace CM */
