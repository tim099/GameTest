#include "class/game/ageOfCube/map/TaskGenMap.h"
#include "class/game/ageOfCube/map/Map.h"
namespace AOC{
TaskGenMap::TaskGenMap(AOC::Map* _map,glm::ivec3 _map_size,unsigned _seed,int _ground_height) {
	map=_map;
	map_size=_map_size;
	seed=_seed;
	ground_height=_ground_height;
}
TaskGenMap::~TaskGenMap() {

}
void TaskGenMap::ExecuteTask(){
	map->gen_map(map_size,seed,ground_height);
}
}
