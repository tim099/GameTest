#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
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
	UI::UI *UI;
	ChessBoard *chess_board;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENESTART_H_ */
