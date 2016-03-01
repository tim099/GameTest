#include "class/game/map/landscape/tree/Tree.h"
#include "class/game/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"

#include <iostream>
DrawObject *Tree::tree_Drawobj=0;

void Tree::landscape_pre_init(){
	std::cout<<"Tree::pre_init()"<<std::endl;
	tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/pinetree");
	//tree_Drawobj=AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
}
Tree::Tree() {
	tree_type=pine_tree;
	pos=0;
}
Tree::~Tree() {
	if(pos)delete pos;
	//std::cout<<"delete tree"<<std::endl;
}
void Tree::set_pos(int x,int y,int z){
	if(!pos){
		pos=new Position(glm::vec3(Map::CUBE_SIZE*x+0.45,Map::CUBE_SIZE*y+0.45,
				Map::CUBE_SIZE*z+0.45));
		//pos->set_scale(glm::vec3(2.0,2.0,2.0));
	}
}
void Tree::draw(){
	/*
	if(!pos){
		pos=new Position(glm::vec3(Map::CUBE_SIZE*x+0.45,Map::CUBE_SIZE*y+0.45,
				Map::CUBE_SIZE*z+0.45));
		//pos->set_scale(glm::vec3(2.0,2.0,2.0));
	}
	*/
	tree_Drawobj->push_temp_drawdata(new DrawDataObj(pos));
	//std::cout<<"draw tree"<<std::endl;
}
