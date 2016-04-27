#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/array/Array3D.h"
#include "class/tim/array/Array2D.h"
#include "class/display/draw/drawObject/DynamicDrawObject.h"
#include "class/display/model/cube/CubeModel.h"
#include "class/tim/math/Position.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/lua/Lua.h"
#include "class/game/chessMaster/chessboard/Rule.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/game/chessMaster/chessboard/BoardMCT.h"
namespace CM {

class ChessBoard : public Tim::GlobalObject<ChessBoard>{
public:
	ChessBoard(int sizex=8,int sizey=3,int sizez=8);
	virtual ~ChessBoard();


	void draw();

	bool set_type(int x,int y,int z,unsigned char val);
	int get_type(int x,int y,int z);

	bool set_type(int x,int y,short int val);

	Piece* get_piece(int x,int y);
	int get_type(int x,int y);
	void load_script(std::string path);


	void save_board(std::string path);
	void load_board(std::string path);

	void save_pieces(std::string path);
	void load_pieces(std::string path);

	void save_mct();
	void load_mct();
	void find_select_cube();

	void restart();
	void move(Step &step);
	void undo(Step &step);
	void undo();
	void clear();
	void clear_steps();
	void next_turn(CM::Step step);

	inline void find_next_step(Tim::Array2D<short int> *chess_board,
			int x,int y,std::vector<CM::Step> &next_steps){
		int type=chess_board->get(x,y);
		int player=1;
		if(type<0){
			type*=-1;
			player=-1;
		}
		type-=1;
		pieces[type]->next_step(chess_board,x,y,next_steps,player);
	}
	void find_next_step(Tim::Array2D<short int> *chess_board,
			int player,std::vector<CM::Step> &next_steps);
	static int get_board(lua_State *L);
	static int find_board(lua_State *L);

	bool bound_check(int x,int y);
	void backpropagation();
	inline int check_winner(Tim::Array2D<short int> *chess_board){
		return rule->check_winner(chess_board);
	}
	int evaluate_score(Tim::Array2D<short int> *chess_board,int player);

	//cube being selected by mouse
	glm::ivec3 selected_cube;

	//cube being selected on(may near by the selected cube or equal to selected cube
	glm::ivec3 selected_on;

	glm::ivec2 selected_piece;
	double cube_size;
	std::vector<Piece*>pieces;

	Tim::Array2D<short int> *chess_board;//all chess on the board
	Tim::Array3D<unsigned char> *board;//the chess_board's structure
	std::vector<CM::Step*> steps;
	int cube_type_num;//number of cube type

	inline Tim::Array2D<short int>* get_cur()const{
		return cur_board;
	}
	inline CM::StepNode *get_cur_node(){
		return cur_node;
	}
	CM::BoardMCT *mct;
	int winner,cur_player;
	glm::ivec3 size;
protected:
	void init_board();
	void gen_model();
	void find_selected_on(glm::vec3 pos);
	void find_selected_cube(glm::vec3 pos);
	std::string tex_path;
	std::string normal_path;
	std::string dir_path;
	Display::DynamicDrawObject *dboard;
	Display::CubeModel *cube;
	Position *pos;


	CM::StepNode *cur_node;

	CM::Rule *rule;
	std::string rule_path;
	bool updated;

	Tim::Array2D<short int> *cur_board;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_ */
