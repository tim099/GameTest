/*
 * PlayerUI.h
 *
 *  Created on: 2016�~6��9��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_
#define SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_

#include <string>
#include "class/display/UI/UI.h"

namespace AOC{
	class Player;
}

namespace UI {

class PlayerUI :public UI {
public:
	PlayerUI();
	virtual ~PlayerUI();
	virtual UIObject* create_UIObject(){
		return new PlayerUI();
	}
	virtual std::string get_type()const{
		return "PlayerUI";
	}
	bool check_script();
protected:

};

} /* namespace AOC */

#endif /* SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_ */
