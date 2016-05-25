#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#include "class/game/ageOfCube/map/landscape/Landscape.h"
#include "class/tim/math/Position.h"
#include <iostream>

namespace Display{
class DrawObject;
}
namespace AOC{
class Tree : public AOC::Landscape{
	static const float max_tree_size=10.0;
	static const unsigned char pine_tree=0;
public:
	Tree();
	Tree(Tree* tree);
	virtual ~Tree();
	virtual void landscape_pre_init();
	virtual AOC::Landscape* create_landscape(){
		return new Tree(this);
	}
	virtual std::string get_name()const{
		return "Tree";
	}
	virtual math::vec3<int> get_cube_large_size();
	virtual bool draw_cube(){
		return true;
	}
	virtual void landscape_update();
	virtual void set_pos(int x,int y,int z);
	virtual void draw();
	void rand_tree_size();
	math::Position *pos;
	unsigned char tree_type;
protected:
	void gen_pos();
	virtual void save_landscape(FILE * file);
	virtual void load_landscape(FILE * file);
	float size;
	//int reproduce_time,age,max_age;
	Display::DrawObject *tree_Drawobj;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_ */
