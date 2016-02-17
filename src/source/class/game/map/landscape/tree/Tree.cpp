#include "class/game/map/landscape/tree/Tree.h"
#include "class/game/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"

#include <iostream>
DrawObject *Tree::tree_Drawobj=0;
Tree::Tree() {
	tree_type=pine_tree;
	pos=0;
}
Tree::~Tree() {
	if(pos)delete pos;
}
void Tree::draw(){
	if(!tree_Drawobj){
		tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/pinetree");
		//tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
	}
	if(!pos){
		pos=new Position(glm::vec3(Map::CUBE_SIZE*x+0.45,Map::CUBE_SIZE*y+0.45,
				Map::CUBE_SIZE*z+0.45));
	}
	tree_Drawobj->push_temp_drawdata(new DrawDataObj(pos));
	//std::cout<<"draw tree"<<std::endl;
}
