#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
#include <class/game/chessMaster/chessboard/ChessBoard.h>
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
namespace CM {
namespace scene{
class SceneStart : public Scene{
public:
	SceneStart();
	virtual ~SceneStart();
	virtual std::string scene_name()const{
		return "SceneStart";
	}

	virtual void pause();
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume();
	std::string local_path;
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Signal *sig);
	void handle_input();
	void camera_control();
	void draw_step();

	void AI_move(int player);
	CM::Step best_step(int player,int depth,int pruning);

	void next_turn(CM::Step step);
	UI::UI *UI;
	ChessBoard *chess_board;
	Camera* camera;
	Camera* p1camera,*p2camera;
	std::vector<CM::Step*> steps;

	LightControl* lightControl;
	std::vector<glm::ivec2> next_step;
	int turn;
	bool destruct_mode;
	int type;
	bool selected;
	int sx,sy;
	int prev_sx,prev_sy;
	long long unsigned total_compute;
	bool do_pruning;
	int difficulty;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_ */
