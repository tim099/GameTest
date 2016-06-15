#ifndef SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_
#define SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_

#include "class/game/ageOfCube/map/cube/CubeLarge.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/tim/math/Position.h"
#include "class/game/ageOfCube/player/resource/ResourceModifier.h"

namespace AOC {
class Map;
class Building: public CubeLarge, public Unit

{
public:
	Building();
	virtual ~Building();
	virtual void building_pre_init();
	virtual AOC::Building* get_building(){
		return this;
	}
	virtual AOC::Building* clone(){
		return 0;
	}
	virtual std::string get_name()const{
		return "Building";
	}
	virtual void set_pos(int x,int y,int z);
	virtual math::vec3<double> get_size();
	virtual math::vec3<double> get_rotate();
	virtual math::vec3<double> get_pos();
	virtual math::vec3<double> get_mid_pos();
	virtual math::vec3<int> get_pos_int();
	virtual math::vec3<int> get_mid_pos_int();
	virtual bool draw_cube(){return true;}

	void set_rotate(int _rotate);
	inline int get_rotate_int()const{return rotate;}

	void draw_buildable(Map *map);
	void set_size(float size);
	virtual void draw();
	bool create_building();

	void upgrade_building(std::string description);
	ResourceModifier get_build_cost(){return build_cost;}
protected:
	virtual void unit_update();
	virtual void building_set_pos(int x,int y,int z);
	virtual void building_update(){}
	virtual void save_cubeEX(FILE * file);
	virtual void load_cubeEX(FILE * file);
	virtual void save_building(FILE * file){}
	virtual void load_building(FILE * file){}
	virtual void draw_building(){}
	void draw_hp();

	float size;
	math::Position pos;

	ResourceModifier build_cost;
private:
	int rotate;
};
}

#endif /* SOURCE_CLASS_GAME_MAP_BUILDING_BUILDING_H_ */
