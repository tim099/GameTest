#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#include "class/game/ageOfCube/map/landscape/Landscape.h"
#include "class/tim/math/Position.h"
namespace Display{
class DrawObject;
}
namespace AOC{
class Tree : public AOC::Landscape{
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
	virtual bool draw_cube(){
		return true;
	}
	virtual void set_pos(int x,int y,int z);
	virtual void draw();
	math::Position *pos;
	unsigned char tree_type;
protected:
	virtual void save_landscape(FILE * file);
	virtual void load_landscape(FILE * file);
	Display::DrawObject *tree_Drawobj;
};
}
#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_ */
