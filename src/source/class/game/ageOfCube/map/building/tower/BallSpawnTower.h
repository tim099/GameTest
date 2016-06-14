#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_BALLSPAWNTOWER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_BALLSPAWNTOWER_H_
#include "class/game/ageOfCube/map/building/Building.h"

#include <cmath>
namespace Display{
class DrawObject;
}
namespace AOC {

class BallSpawnTower : public Building{
public:
	BallSpawnTower();
	BallSpawnTower(BallSpawnTower* tower);
	virtual ~BallSpawnTower();
	virtual void building_pre_init();
	virtual math::vec3<int> get_cube_large_size(){
		return math::vec3<int>(ceil(size),ceil(size),ceil(size));
	}
	virtual AOC::Building* clone(){
		return new BallSpawnTower(this);
	}
	virtual std::string get_name()const{
		return "BallSpawnTower";
	}
protected:
	virtual void building_set_pos(int x,int y,int z);
	virtual void save_building(FILE * file);
	virtual void load_building(FILE * file);
	virtual void building_update();
	virtual void draw_building();
	void init_BallSpawnTower();
	void spawn();
	Display::DrawObject *tower_Drawobj;
	Display::DrawObject *tower_part1;
	Display::DrawObject *tower_part2;
	Display::DrawObject *tower_part3;
	Display::DrawObject *tower_part4;
	math::Position part0_pos;
	math::Position part1_pos1,part1_pos2;
	math::Position part2_pos;
	math::Position part3_pos;
	math::Position part4_pos;
	math::Position ball1;
	math::Position ball2;
	math::Position ball3;
	math::Position ball4;
	int loop_time;
	int loop_count;
	int timer;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_TOWER_BALLSPAWNTOWER_H_ */
