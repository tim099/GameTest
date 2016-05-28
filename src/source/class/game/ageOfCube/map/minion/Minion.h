#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_

#include "class/game/ageOfCube/unit/Unit.h"
#include "class/physic/RigidBody.h"
namespace Display{
	class DrawObject;
}
namespace AOC {

class Minion: public Unit{
public:
	Minion();
	virtual ~Minion();
	virtual void minion_pre_init(){}
	virtual void unit_update();

	virtual Minion* create_minion()=0;


	void save(FILE * file);
	void load(FILE * file);
	void recruit();
	void draw();

	inline math::vec3<double>get_position()const{return rigid_body.pos;}
	inline void set_position(math::vec3<double> pos){rigid_body.pos=pos;}

protected:
	virtual void save_minion(FILE * file){}
	virtual void load_minion(FILE * file){}
	virtual void draw_minion()=0;
	virtual void minion_update(){}

	void push_minion_to_controller();
	physic::RigidBody rigid_body;
	bool minion_created;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_ */
