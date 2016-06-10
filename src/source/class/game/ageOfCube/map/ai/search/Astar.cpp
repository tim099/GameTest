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
	thread_pool=new Tim::ThreadPool(1,BELOW_NORMAL_PRIORITY_CLASS);//IDLE_PRIORITY_CLASS
	node_pool=new Tim::ObjPool<Node>(10000);
	register_cur();
}
Astar::~Astar() {
	thread_pool->Terminate();
	delete node_pool;
}
void Astar::search(Tim::SmartPointer<Finder>& finder){
	std::vector<Node*>nodes;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >visited;
	//std::set<math::vec3<int>,math::vec3Cmp<int> >in_q;
	std::map<math::vec3<int>,Node*,math::vec3Cmp<int> >::iterator it;
	std::priority_queue<Node*, std::vector<Node*>, NodeCmp > q;
	double d_size=finder->get_double_size();
	int size=finder->get_size(),r=floor((d_size/2.0)/Map::CUBE_SIZE),search_times=0;

	int max_search_times=finder->max_search_times,min_search_times=finder->min_search_times;
	bool find=false,access_able,standable,jumpable;
	double min_dis=std::numeric_limits<double>::max();
	unsigned char path;
	bool next_node_jump;
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
	//std::cout<<"size="<<size<<std::endl;
	while(!q.empty()&&search_times<max_search_times&&
			(search_times<min_search_times||!find)){
		search_times++;
		node=q.top();
		q.pop();

		if(finder->check_find(node)){//find!!
			find=true;
			if(node->cur_dis<min_dis){
				min_dis=node->cur_dis;
				find_node=node;
			}
		}

		//===================find next step====================
		cur_stand_on=node->pos;
		cur_stand_on.x+=r;
		cur_stand_on.y-=1;
		cur_stand_on.z+=r;
		standable=map->get_standable(cur_stand_on.x,cur_stand_on.y,cur_stand_on.z);
		jumpable=map->get_jumpable(cur_stand_on.x,cur_stand_on.y,cur_stand_on.z);
		next_node_pos.clear();
		path=0;
		if(standable||node->jump){
			next_node_pos.push_back(math::vec3<int>(1,0,0));
			next_node_pos.push_back(math::vec3<int>(-1,0,0));
			next_node_pos.push_back(math::vec3<int>(0,0,1));
			next_node_pos.push_back(math::vec3<int>(0,0,-1));
		}
		if(standable&&jumpable){
			next_node_pos.push_back(math::vec3<int>(0,1,0));//jump
		}
		next_node_pos.push_back(math::vec3<int>(0,-1,0));//drop

		for(unsigned n=0;n<next_node_pos.size();n++){
			next_pos=(node->pos+next_node_pos.at(n));
			it=visited.find(next_pos);
			if(next_node_pos.at(n).y==1){
				next_node_jump=true;
			}else{
				next_node_jump=false;
			}
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
					next_node->init(node);

					next_node->pos=next_pos;
					visited[next_node->pos]=next_node;
					nodes.push_back(next_node);
				}
			}
			if(access_able){
				next_node->cur_dis=node->cur_dis+Map::CUBE_SIZE*next_node_pos.at(n).get_length();
				next_node->parent=node;

				next_node->jump=next_node_jump;
				next_node->score=finder->node_score(next_node);

				q.push(next_node);
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
	if(find){
		//std::cout<<"Astar::search find!!search times="<<search_times<<std::endl;
		finder->find=true;
	}else{
		//std::cout<<"Astar::search not find!!search times="<<search_times<<std::endl;
	}


}


}
}
} /* namespace AI */
