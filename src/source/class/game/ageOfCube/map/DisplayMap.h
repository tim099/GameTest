#ifndef DISPLAYMAP_H_
#define DISPLAYMAP_H_
#include "class/game/ageOfCube/map/MapDrawObject.h"
#include "class/game/ageOfCube/map/WaterDrawObject.h"
#include "class/display/model/cube/CubeModel.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/tim/array/Array2D.h"
#include "class/tim/math/vec3.h"
#include "class/tim/math/vec2.h"
#include <queue>
namespace Tim{
	class ThreadPool;
}
namespace Display{
class Camera;
class Window;
}


namespace math{
class Position;
}
namespace AOC{
class Map;
class DisplayMap {
public:
	DisplayMap(AOC::Map *map);
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



	void draw_map(Display::Camera *camera,Tim::ThreadPool* threadpool);

	void display_height_alter(int val,Tim::ThreadPool* threadpool);
	void update_map(math::vec3<int> pos);

	Tim::Mutex* createMapObjectMutex;
	int display_range,display_height;
	math::vec3<double>dp_start,dp_end;
protected:
	void gen_display_map_seg();
	math::vec2<int> get_seg_pos(Display::Camera *camera);
	void get_draw_range(Display::Camera *camera,math::vec2<int> &start,math::vec2<int> &end);
	void get_draw_range(Display::Camera *camera,math::vec3<double> &start,math::vec3<double> &end);
	Tim::Array2D<MapDrawObject*>*dmaps;
	Tim::Array2D<WaterDrawObject*>*water_dmaps;
	Display::CubeModel *cube;
	AOC::Map *map;
	math::Position *pos;
	math::vec2<int>dp_s,dp_e;

	math::vec3<int> seg;
	math::vec3<int> segsize;
};
}
#endif /* DISPLAYMAP_H_ */
