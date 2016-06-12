/*
 * PlayerUI.h
 *
 *  Created on: 2016¦~6¤ë9¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_
#define SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_

#include <string>
#include "class/display/UI/UI.h"
#include "class/display/UI/string/UIString.h"

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
	void init_playerUI();
	void set_resource_amount(unsigned int resource_string_id, int value);
	void set_score(int score);
private:
	UIString *resource_amount_strings[6];
	UIString *score_string;
	bool inited;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_ */
