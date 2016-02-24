#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_
#include "class/game/map/landscape/Landscape.h"
#include "class/tim/math/Position.h"
class DrawObject;
class Tree : public Landscape{
	static const unsigned char pine_tree=0;

	static DrawObject *tree_Drawobj;

public:
	Tree();
	virtual ~Tree();
	virtual void landscape_pre_init();
	virtual Landscape* create_landscape(){
		return new Tree();
	}
	virtual std::string get_name()const{
		return "Tree";
	}
	virtual bool draw_cube(){
		return true;
	}
	virtual void draw();
	Position *pos;
	unsigned char tree_type;
};

#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_TREE_H_ */
