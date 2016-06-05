#include "class/game/ageOfCube/map/ai/search/Astar.h"
#include "class/game/ageOfCube/map/Map.h"
#include <queue>
#include <vector>
#include <iostream>
#include <limits>
#include <set>
namespace AOC {
namespace AI {
namespace search{
Astar::Astar() {
	thread_pool=new Tim::ThreadPool(1,BELOW_NORMAL_PRIORITY_CLASS);
	node_pool=new Tim::ObjPool<Node>(50000);
}
Astar::~Astar() {
	delete node_pool;
	thread_pool->Terminate();
}
void Astar::search(Tim::SmartPointer<Finder>& finder){
	std::vector<Node*>nodes;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >visited;
	std::set<math::vec3<int>,math::vec3Cmp<int> >in_q;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >::iterator it;
	std::priority_queue<Node*, std::vector<Node*>, NodeCmp > q;

	int size=finder->get_size();
	int search_times=0;
	int max_search_times=finder->max_search_times,min_search_times=finder->min_search_times;
	bool access_able;
	bool find=false;
	double min_dis=std::numeric_limits<double>::max();
	Map *map=Map::get_cur_object();
	Node *next_node,*find_node=0;
	std::vector<math::vec3<int> >next_node_pos;
	math::vec3<int> next_pos;
	math::vec3<int> cur_stand_on;
	bool standable;

	Node* node=new Node();//start!!
	node->pos=finder->get_start_pos();
	visited[node->pos]=node;
	q.push(node);
	nodes.push_back(node);
	Cube* cube;
	//std::cout<<"size="<<size<<std::endl;
	while(!q.empty()&&search_times<max_search_times&&
			(search_times<min_search_times||!find)){
		//std::cout<<"Astar::search times="<<search_times<<std::endl;
		search_times++;
		node=q.top();
		q.pop();
		in_q.erase(node->pos);
		//std::cout<<"node score="<<node->score<<std::endl;
		if(finder->check_find(node)){//find!!
			find=true;
			if(node->cur_dis<min_dis){
				min_dis=node->cur_dis;
				find_node=node;
			}
		}

		//===================find next step====================
		cur_stand_on=node->pos;
		cur_stand_on.x+=size/2;
		cur_stand_on.y-=1;
		cur_stand_on.z+=size/2;
		cube=map->get_cube(cur_stand_on.x,cur_stand_on.y,cur_stand_on.z);
		if(cube->standable()){
			standable=true;
		}else{
			standable=false;
		}
		next_node_pos.clear();
		if(standable||node->jump){
			//if(node->jump)std::cout<<"jump"<<std::endl;
			next_node_pos.push_back(node->pos+math::vec3<int>(1,0,0));
			next_node_pos.push_back(node->pos+math::vec3<int>(-1,0,0));
			next_node_pos.push_back(node->pos+math::vec3<int>(0,0,1));
			next_node_pos.push_back(node->pos+math::vec3<int>(0,0,-1));
		}
		if(standable&&cube->jumpable()){
			next_node_pos.push_back(node->pos+math::vec3<int>(0,1,0));//jump
		}
		next_node_pos.push_back(node->pos+math::vec3<int>(0,-1,0));//drop
		//std::cout<<"next_node_pos.size()="<<next_node_pos.size()<<std::endl;

		for(unsigned n=0;n<next_node_pos.size();n++){
			next_pos=next_node_pos.at(n);
			it=visited.find(next_pos);
			if(it!=visited.end()){//visited!!
				if(node->cur_dis+Map::CUBE_SIZE>=it->second->cur_dis){//no updated
					continue;
				}else{
					//std::cout<<"update!!"<<node->cur_dis+Map::CUBE_SIZE
							//<<","<<it->second->cur_dis<<std::endl;


					access_able=true;
					next_node=it->second;
					if(!(next_pos==next_node->pos)){
						std::cout<<"update!!pos="<<next_pos.x<<","<<next_pos.y<<","<<next_pos.z<<std::endl;
						std::cout<<"update!!pos2="<<next_node->pos.x<<","
								<<next_node->pos.y<<","<<next_node->pos.z<<std::endl;
					}

				}
			}else{//first visit!!
				access_able=true;
				for(int i=0;i<size&&access_able;i++){//check if this position can be access
					for(int j=0;j<size&&access_able;j++){
						for(int k=0;k<size&&access_able;k++){
							if(map->get_cube_type(i+next_pos.x,j+next_pos.y,k+next_pos.z)!=Cube::cubeNull){
								access_able=false;
							}
						}
					}
				}
				if(access_able){
					next_node=node_pool->create();
					next_node->pos=next_pos;
					visited[next_node->pos]=next_node;
					nodes.push_back(next_node);
				}
			}
			if(access_able){
				next_node->init(node);
				next_node->cur_dis=node->cur_dis+Map::CUBE_SIZE;
				if(next_pos.y-node->pos.y==1){
					next_node->jump=true;
				}
				next_node->score=finder->node_score(next_node);
				if(in_q.find(next_node->pos)==in_q.end()){
					q.push(next_node);
					in_q.insert(next_node->pos);
				}

				//std::cout<<"next_pos added"<<std::endl;
			}
		}
	}
	if(find_node){
		finder->find_node(find_node);
	}

	for(unsigned i=0;i<nodes.size();i++){
		node_pool->free(nodes.at(i));
	}
	finder->search_done=true;
	if(find){
		std::cout<<"Astar::search find!!search times="<<search_times<<std::endl;
		finder->find=true;
	}else{
		std::cout<<"Astar::search not find!!search times="<<search_times<<std::endl;
	}
}


}
}
} /* namespace AI */
