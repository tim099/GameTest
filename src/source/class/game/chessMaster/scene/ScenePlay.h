#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include "class/audio/AudioPlayer.h"

namespace CM {
class AI;
namespace scene{
class ScenePlay: public Scene {
	static const int MAX=999999;
public:
	ScenePlay();
	virtual ~ScenePlay();
	virtual std::string scene_name()const{
		return "ScenePlay";
	}
	virtual void pause();
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume();

	virtual void loading();
	std::string local_path;
protected:

	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Input::Signal *sig);
	void player_move_chess();
	void handle_input();
	void camera_control();
	void draw_step();
	void restart();
	void AI_move(int player);

	void next_turn(CM::Step step);

	math::Position back_ground_pos;
	UI::UI *UI;
	ChessBoard *chess_board;
	Display::Camera* camera;
	Display::Camera* p1camera,*p2camera;
	Audio::AudioPlayer *back_music;
	CM::AI *ai;

	Display::LightControl* lightControl;
	Tim::vector<CM::Step> next_step;

	int simulation_times;
	bool selected;
	bool player_move;
	glm::ivec2 s;
	int prev_sx,prev_sy;
	int difficulty;
	int AI_mode;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_ */
