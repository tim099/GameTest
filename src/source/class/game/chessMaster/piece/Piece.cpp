#include "class/game/chessMaster/piece/Piece.h"
#include "class/display/draw/drawObject/DrawObject.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"

#include <fstream>
namespace CM {

Piece::Piece() {
	draw_piece1=0;
	draw_piece2=0;
	type=1;
	rule=0;
}
Piece::~Piece() {
	if(rule)delete rule;
}
int Piece::bound_check(lua_State *L){
	int y = lua_tonumber(L, -1);
	lua_pop(L,1);
	int x = lua_tonumber(L, -1);
	lua_pop(L,1);
	//std::cout<<"x="<<x<<",y="<<y<<std::endl;
	if(ChessBoard::get_cur_object()->bound_check(x,y)){
		lua_pushnumber(L,1);
	}else{
		lua_pushnumber(L,0);
	}
	return 1;
}
int Piece::get_board(lua_State *L){
	int y = lua_tonumber(L, -1);
	lua_pop(L,1);
	int x = lua_tonumber(L, -1);
	lua_pop(L,1);

	int type=ChessBoard::get_cur_object()->get_type(x,y);
	lua_pushnumber(L,type);

	return 1;
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
			draw_piece1=AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="draw_piece2:"){
			Tim::String::get_line(is, line, true, true);
			draw_piece2=AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="rule_path:"){//.lua file
			Tim::String::get_line(is, rule_path, true, true);
		}else if(line!=""){
			std::cerr<<"Piece::load_script unknown script:"<<line<<std::endl;
		}

	}
	if(rule)delete rule;
	rule=new Tim::Lua();
	rule->loadfile(rule_path);
	rule->rigister_function("bound_check",Piece::bound_check);
	rule->rigister_function("get_board",Piece::get_board);
	rule->p_call(0,0,0);
	//std::cout<<"str = "<<lua_tostring(rule->L,1)<<std::endl;
    //std::cout<<"str = "<<rule->get_string("str")<<std::endl;
    //std::cout<<"str = "<<lua_tostring(rule->L,-1)<<std::endl;
}
void Piece::next_step(glm::ivec2 cur_step,std::vector<glm::ivec2> &next_step,bool player1){
	rule->get_global("next_step");
	rule->push_number(cur_step.x);
	rule->push_number(cur_step.y);
	if(player1){
		rule->push_number(1);
	}else{
		rule->push_number(-1);
	}
	rule->p_call(3,1,0);


	std::vector<int> table;
	rule->get_table(table);
	int step_num=table.size()/2;
	//std::cout<<"step_num="<<step_num<<std::endl;
	for(int i=0;i<step_num;i++){
		int x=table.at(2*i),y=table.at(2*i+1);
		next_step.push_back(glm::ivec2(x,y));
		//std::cout<<"step="<<x<<","<<y<<std::endl;
	}
	rule->pop(1);//pop next_step
}
void Piece::draw(Position* pos,bool player1){
	if(player1){
		draw_piece1->push_temp_drawdata(new DrawDataObj(pos));
	}else{
		draw_piece2->push_temp_drawdata(new DrawDataObj(pos));
	}
}


} /* namespace CM */
