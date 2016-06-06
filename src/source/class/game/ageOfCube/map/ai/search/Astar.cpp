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
	node_pool=new Tim::ObjPool<Node>(10000);
}
Astar::~Astar() {
	thread_pool->Terminate();
	delete node_pool;
}
void Astar::search(Tim::SmartPointer<Finder>& finder){
	std::vector<Node*>nodes;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >visited;
	std::set<math::vec3<int>,math::vec3Cmp<int> >in_q;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >::iterator it;
	std::priority_queue<Node*, std::vector<Node*>, NodeCmp > q;

	int size=finder->get_size(),search_times=0;
	int max_search_times=finder->max_search_times,min_search_times=finder->min_search_times;
	bool find=false,access_able;
	double min_dis=std::numeric_limits<double>::max();
	unsigned char path;
	static const unsigned char left=1<<0;
	static const unsigned char right=1<<1;
	static const unsigned char front=1<<2;
	static const unsigned char back=1<<3;
	Map *map=Map::get_cur_object();
	Node *next_node,*find_node=0;
	std::vector<math::vec3<int> >next_node_pos;
	math::vec3<int> next_pos;
	math::vec3<int> cur_stand_on;

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
		next_node_pos.clear();
		path=0;
		if(cube->standable()||node->jump){
			next_node_pos.push_back(math::vec3<int>(1,0,0));
			next_node_pos.push_back(math::vec3<int>(-1,0,0));
			next_node_pos.push_back(math::vec3<int>(0,0,1));
			next_node_pos.push_back(math::vec3<int>(0,0,-1));
		}
		if(cube->standable()&&cube->jumpable()){
			next_node_pos.push_back(math::vec3<int>(0,1,0));//jump
		}
		next_node_pos.push_back(math::vec3<int>(0,-1,0));//drop

		for(unsigned n=0;n<next_node_pos.size();n++){
			next_pos=(node->pos+next_node_pos.at(n));
			it=visited.find(next_pos);
			if(it!=visited.end()){//visited!!
				if(node->cur_dis+Map::CUBE_SIZE>=it->second->cur_dis){//no updated
					continue;
				}else{
					access_able=true;
					next_node=it->second;
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
				next_node->cur_dis=node->cur_dis+Map::CUBE_SIZE*next_node_pos.at(n).get_length();

				if(next_node_pos.at(n).y==1){
					next_node->jump=true;
				}
				next_node->score=finder->node_score(next_node);
				if(in_q.find(next_node->pos)==in_q.end()){
					q.push(next_node);
					in_q.insert(next_node->pos);
				}
				if(next_node_pos.at(n).x==1){
					path|=right;
				}else if(next_node_pos.at(n).x==-1){
					path|=left;
				}else if(next_node_pos.at(n).z==1){
					path|=front;
					if(path&right){
						next_node_pos.push_back(math::vec3<int>(1,0,1));
					}
					if(path&left){
						next_node_pos.push_back(math::vec3<int>(-1,0,1));
					}
				}else if(next_node_pos.at(n).z==-1){
					path|=back;
					if(path&right){
						next_node_pos.push_back(math::vec3<int>(1,0,-1));
					}
					if(path&left){
						next_node_pos.push_back(math::vec3<int>(-1,0,-1));
					}
				}
			}
		}
	}


	if(find_node){
		finder->node_find(find_node);
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
