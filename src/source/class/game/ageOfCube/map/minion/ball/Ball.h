#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_

#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/tim/pointer/SmartPointer.h"
#include "class/game/ageOfCube/map/ai/search/finder/FindPath.h"
#include "class/audio/AudioPlayer.h"

namespace AOC {

class Ball: public Minion {
	static const float gravity=-0.003f;
public:
	virtual void minion_pre_init();
	Ball();
	Ball(Ball* ball);
	virtual ~Ball();

	virtual Minion* clone(){
		return new Ball(this);
	}
	virtual std::string get_name()const{
		return "Ball";
	}

protected:
	virtual void save_minion(FILE * file);
	virtual void load_minion(FILE * file);
	virtual void draw_minion();
	virtual void minion_update();
	virtual void killed();
	virtual void unit_create();
	void ball_move();
	void find_path();
	//void explode();
	void moving();
	//unsigned target_id;
	Display::DrawObject *ball_Drawobj;

	Tim::SmartPointer<AI::search::Finder> *finder;
	int timer,stuck_timer,stuck_times,colli_timer;

};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_ */
