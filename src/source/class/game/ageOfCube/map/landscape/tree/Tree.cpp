#include "class/game/ageOfCube/map/landscape/tree/Tree.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/landscape/LandscapeCreator.h"
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>
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
	//reproduce_time=0;
	//age=0;
	//max_age=35+rand()%20;
}
Tree::Tree(Tree* tree) {
	tree_type=tree->tree_type;
	tree_Drawobj=tree->tree_Drawobj;
	pos=0;
	size=tree->size;
	//reproduce_time=0;
	//age=0;
	//max_age=30+rand()%30;
}
Tree::~Tree() {
	if(pos)delete pos;
	//std::cout<<"delete tree"<<std::endl;
}
void Tree::landscape_update(){
	//std::cout<<"Tree::update()"<<std::endl;
	/*
	if(size<max_tree_size){
		size+=0.05;
		size*=1.01;
	}
	if(age>20){
		reproduce_time++;
		if(reproduce_time>15&&(rand()%2)==0){
			bool reproduce=false;
			LandscapeCreator* lc=LandscapeCreator::get_cur_object();
			Map *map=Map::get_cur_object();
			Tree* new_tree=(Tree*)lc->create("Tree");
			new_tree->size=0.25;
			int px,py,pz;
			for(int i=0;i<10;i++){
				px=(rand()%5)-2;
				py=(rand()%5)-2;
				pz=(rand()%5)-2;
				if(!reproduce&&new_tree->build(map,x+px,y+py,z+pz)){
					reproduce=true;
					break;
				}
			}

			if(!reproduce){
				delete new_tree;//plant fail
			}else{
				reproduce_time=0;
				size*=0.5;
			}
		}

	}
	gen_pos();
	age++;
	if(age>max_age){//die
		Map::get_cur_object()->remove_cube(x,y,z);
	}
	*/
}
math::vec3<int> Tree::get_cube_large_size(){
	return math::vec3<int>(ceil(0.35*size),ceil(size),ceil(0.35*size));
}
void Tree::rand_tree_size(){
	size=1.25*sqrt((rand()%101))+0.4;
	if(size>max_tree_size)size=max_tree_size;
}
void Tree::save_landscape(FILE * file){
	fprintf(file,"%c %f\n",(char)tree_type,size);
}
void Tree::load_landscape(FILE * file){
	fscanf(file,"%c %f\n",(char*)&tree_type,&size);
}
void Tree::gen_pos(){
	math::vec3<int> real_size=get_cube_large_size();
	pos->set_pos(glm::vec3(AOC::Map::CUBE_SIZE*x+0.5*real_size.x,
			AOC::Map::CUBE_SIZE*y+0.5*size,
			AOC::Map::CUBE_SIZE*z+0.5*real_size.z));
	pos->set_scale(glm::vec3(size,size,size));
}
void Tree::set_pos(int x,int y,int z){
	if(!pos){
		pos=new math::Position();
		gen_pos();
	}
}
void Tree::draw(){
	tree_Drawobj->push_temp_drawdata(new Display::DrawDataObj(pos));
	//std::cout<<"draw tree"<<std::endl;
}
}
