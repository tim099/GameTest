#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"

#include <fstream>
namespace CM {

Piece::Piece() {
	weight=1;
	draw_piece1=0;
	draw_piece2=0;
	//type=1;
	rule=0;
	rule_mutex=new Tim::Mutex();
}
Piece::~Piece() {
	if(rule)delete rule;
	delete rule_mutex;
}
void Piece::load_script(std::string path){
	std::filebuf file;
	file.open(path.c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Piece::load_script fail,file:" << path
				<< " open fail" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;
	while(Tim::String::get_line(is, line, true, true)&&line!="#END"){
		if(line=="draw_piece1:"){
			Tim::String::get_line(is, line, true, true);
			draw_piece1=Display::AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="draw_piece2:"){
			Tim::String::get_line(is, line, true, true);
			draw_piece2=Display::AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="rule_path:"){//.lua file
			Tim::String::get_line(is, rule_path, true, true);
		}else if(line=="weight:"){//.lua file
			Tim::String::get_line(is, line, true, true);
			sscanf(line.c_str(),"%d",&weight);
		}else if(line!=""){
			std::cerr<<"Piece::load_script unknown script:"<<line<<std::endl;
		}

	}
	if(rule)delete rule;
	rule=new Tim::Lua();
	rule->loadfile(rule_path);
	//rule->rigister_function("bound_check",ChessBoard::bound_check);
	rule->rigister_function("get_board",ChessBoard::get_board);
	rule->p_call(0,0,0);
}
void Piece::next_step(Tim::Array2D<short int> *chess_board,
		int x,int y,std::vector<int> &next_step,int player){
	rule_mutex->wait_for_this();
	//ChessBoard::get_cur_object()->set_current(chess_board);
	rule->pushlightuserdata(chess_board);
	rule->set_global("board");

	rule->get_global("next_step");
	rule->push_number(x);
	rule->push_number(y);
	rule->push_number(player);

	rule->p_call(3,1,0);

	rule->get_table(next_step);

	rule->pop(1);//pop next_step

	rule_mutex->release();
}
void Piece::next_step(Tim::Array2D<short int> *chess_board,
		int x,int y,std::vector<CM::Step> &next_steps,int player){
	std::vector<int> next;
	next.reserve(120);
	next_step(chess_board,x,y,next,player);
	CM::Step next_step;
	int i=0;
	while(i<(int)next.size()){
		next_step.parse_step(chess_board,x,y,next,i);
		next_steps.push_back(next_step);
	}
}
void Piece::draw(Position* pos,int player){
	if(player==1){
		draw_piece1->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}else{
		draw_piece2->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}
}


} /* namespace CM */
