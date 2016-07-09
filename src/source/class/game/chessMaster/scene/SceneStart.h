#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
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
class SceneStart : public Scene{
	static const int MAX=999999;
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

	virtual void loading();
	std::string local_path;
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Input::Signal *sig);
	void handle_input();
	UI::UI *UI;

	Audio::AudioPlayer *back_music;

};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_ */
