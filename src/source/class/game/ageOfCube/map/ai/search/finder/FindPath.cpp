#include "class/game/ageOfCube/map/ai/search/finder/FindPath.h"
#include "class/game/ageOfCube/map/Map.h"
#include <cmath>
#include <iostream>
namespace AOC {
namespace AI {
namespace search {

FindPath::FindPath(const math::vec3<double>&_pos,const double &_size,math::vec3<int>_des,int _dis) {
	pos=_pos;size=_size;des=_des;dis=_dis;
	des_min=des-dis;
	des_max=des+dis;
	//std::cout<<"des_min="<<des_min.x<<","<<des_min.y<<","<<des_min.z<<std::endl;
	//std::cout<<"des_max="<<des_max.x<<","<<des_max.y<<","<<des_max.z<<std::endl;
	cur_at=0;
}
FindPath::~FindPath() {
	std::cout<<"FindPath::~FindPath()"<<std::endl;
}
double FindPath::node_score(Node* node){
	double total_dis=0;
	math::vec3<int>del_pos=des-node->pos;

	total_dis=node->cur_dis+Map::CUBE_SIZE*(1.5*abs(del_pos.x)+1.5*abs(del_pos.y)+1.5*abs(del_pos.z));
	//std::cout<<"dis_need="<<dis_need<<"score="<<-total_dis<<std::endl;
	return -total_dis;
}
void FindPath::find_node(Node* node){
	convert_path(node);
}
bool FindPath::check_find(Node* node){
	/*
	std::cout<<"des_min="<<des_min.x<<","<<des_min.y<<","<<des_min.z<<std::endl;
	std::cout<<"pos max="<<(node->pos+get_size()).x<<","<<(node->pos+get_size()).y<<","
			<<(node->pos+get_size()).z<<std::endl;
	std::cout<<"des_max="<<des_max.x<<","<<des_max.y<<","<<des_max.z<<std::endl;
	std::cout<<"pos min="<<(node->pos-get_size()).x<<","<<(node->pos-get_size()).y<<","
			<<(node->pos-get_size()).z<<std::endl;
	*/
	if((node->pos+get_size())>=des_min&&
	   (node->pos-get_size())<=des_max){
		return true;
	}
	return false;
}
void FindPath::convert_path(Node* node){
	std::vector<Node*>nodes;
	for(Node* cur=node;cur!=0;cur=cur->parent){
		nodes.push_back(cur);
	}
	math::vec3<double> pos;
	Node* cur;
	int i_size=get_size();
	for(int i=(int)nodes.size()-1;i>=0;i--){
		cur=nodes.at(i);
		pos.x=(cur->pos.x+0.5*i_size)*Map::CUBE_SIZE;
		if(cur->parent&&cur->parent->jump){
			pos.y=(cur->pos.y+0.5*i_size)*Map::CUBE_SIZE;
		}else{
			pos.y=(cur->pos.y)*Map::CUBE_SIZE+0.5*size;
		}
		pos.z=(cur->pos.z+0.5*i_size)*Map::CUBE_SIZE;
		path.push_back(pos);
	}
}
math::vec3<int> FindPath::get_start_pos(){
	return math::vec3<int>(
			(pos.x-0.499*size)/Map::CUBE_SIZE,
			(pos.y-0.499*size)/Map::CUBE_SIZE,
			(pos.z-0.499*size)/Map::CUBE_SIZE);
}
int FindPath::get_size(){
	return ceil(size);
}
} /* namespace search */
} /* namespace AI */
} /* namespace AOC */
