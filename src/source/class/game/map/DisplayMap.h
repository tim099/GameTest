#ifndef DISPLAYMAP_H_
#define DISPLAYMAP_H_
#include "class/game/map/MapDrawObject.h"
#include "class/game/map/WaterDrawObject.h"
#include "class/display/model/cube/CubeModel.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/tim/array/Array2D.h"
#include "class/display/light/LightControl.h"
#include <glm/glm.hpp>
#include <queue>
namespace Tim{
	class ThreadPool;
}
class Map;
class Camera;
class Window;
class Position;
class DisplayMap {
public:
	DisplayMap(Map *map);
	virtual ~DisplayMap();

	void create_map_object(int px,int pz);
	void create_water_object(int px,int pz);
	//generate the whole map's display model
	void gen_map_obj();

	//generate the map's display model in update_maps vectors
	void gen_map_model(Tim::ThreadPool* threadpool,std::vector<glm::ivec2> &update_maps);
	void gen_water_model(Tim::ThreadPool* threadpool,std::vector<glm::ivec2> &update_maps);
	//update the whole maps model
	void update_whole_map();

	void draw_map(Camera *camera,Tim::ThreadPool* threadpool);

	void display_height_alter(int val,Tim::ThreadPool* threadpool);
	void update_map(glm::ivec3 pos);
	void update_water_map(glm::ivec3 pos);
	Tim::Mutex* createMapObjectMutex;
	int range,display_height;
protected:
	void gen_display_map_seg();
	Tim::Array2D<MapDrawObject*>*dmaps;
	Tim::Array2D<WaterDrawObject*>*water_dmaps;
	CubeModel *cube;
	CubeModel *water_cube;
	Map *map;
	Position *pos;

	glm::ivec3 seg;
	glm::ivec3 segsize;
};

#endif /* DISPLAYMAP_H_ */
