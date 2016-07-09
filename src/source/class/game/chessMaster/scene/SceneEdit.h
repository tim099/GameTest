#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_

#include "class/game/scene/Scene.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include "class/audio/AudioPlayer.h"
namespace CM {
namespace scene{
class SceneEdit: public Scene {
public:
	SceneEdit();
	virtual ~SceneEdit();
	virtual std::string scene_name()const{
		return "SceneEdit";
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

	void handle_input();
	void camera_control();

	void init_board();
	math::Position back_ground_pos;
	UI::UI *UI;
	ChessBoard *chess_board;
	Display::Camera* camera;
	Audio::AudioPlayer *back_music;
	//CM::AI *ai;

	Display::LightControl* lightControl;

	bool destruct_mode;
	int type;
	int chess_type;
	glm::ivec2 s;
	//int prev_sx,prev_sy;
	bool edit_chess;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_ */
