#include "class/game/ageOfCube/map/landscape/tree/Tree.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <cstdio>
#include <iostream>
namespace AOC{
void Tree::landscape_pre_init(){
	//std::cout<<"Tree::pre_init()"<<std::endl;
	tree_Drawobj=Display::AllDrawObjects::get_cur_object()->get("landscape/pinetree");
	//tree_Drawobj=Display::AllDrawObjects::get_cur_object()->get("landscape/broadleaftree");
}
Tree::Tree() {
	tree_type=pine_tree;
	tree_Drawobj=0;
	pos=0;
	size=1.0;
}
Tree::Tree(Tree* tree) {
	tree_type=tree->tree_type;
	tree_Drawobj=tree->tree_Drawobj;
	pos=0;
	size=tree->size;
}
Tree::~Tree() {
	if(pos)delete pos;
	//std::cout<<"delete tree"<<std::endl;
}
void Tree::save_landscape(FILE * file){
	fprintf(file,"%c\n",(char)tree_type);
}
void Tree::load_landscape(FILE * file){
	fscanf(file,"%c\n",(char*)&tree_type);
}
void Tree::set_pos(int x,int y,int z){
	if(!pos){
		pos=new math::Position(glm::vec3(AOC::Map::CUBE_SIZE*(x+0.5)
				,AOC::Map::CUBE_SIZE*(y+0.5)+0.45*(size),
				AOC::Map::CUBE_SIZE*(z+0.5)));
		pos->set_scale(glm::vec3(1.3*size,2*size,1.3*size));
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
	tree_Drawobj->push_temp_drawdata(new Display::DrawDataObj(pos));
	//std::cout<<"draw tree"<<std::endl;
}
}
