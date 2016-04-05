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
namespace CM {

class ChessBoard : public Tim::GlobalObject<ChessBoard>{
public:
	ChessBoard(int sizex=8,int sizey=2,int sizez=8);
	virtual ~ChessBoard();
	void init(int sizex,int sizey,int sizez);

	void draw();

	bool set_type(int x,int y,int z,unsigned char val);
	int get_type(int x,int y,int z);

	bool set_type(int x,int y,short int val);
	int get_type(int x,int y);
	void load_script(std::string path);


	void save_board(std::string path);
	void load_board(std::string path);

	void save_pieces(std::string path);
	void load_pieces(std::string path);
	void find_select_cube();

	void move(Step &step);
	void undo(Step &step);
	void find_next_step(glm::ivec2 cur_step,std::vector<glm::ivec2> &next_step);

	bool bound_check(int x,int y);
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
protected:
	void gen_model();
	void find_selected_on(glm::vec3 pos);
	void find_selected_cube(glm::vec3 pos);
	std::vector<Position*>pieces_pos;

	DynamicDrawObject *dboard;
	CubeModel *cube;
	Position *pos;
	bool updated;

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_ */
