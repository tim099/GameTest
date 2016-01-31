#ifndef DISPLAYMAP_H_
#define DISPLAYMAP_H_
#include "class/game/map/MapDrawObject.h"
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

	void gen_map_obj(Tim::ThreadPool* threadpool);
	void gen_map_obj();
	void draw_map(Camera *camera);

	void max_y_alter(int val,Tim::ThreadPool* threadpool);
	void update_map(glm::ivec3 pos);
	Tim::Mutex* createMapObjectMutex;
	int range,max_y;
protected:
	//MapDrawObject* dmaps[SEG][SEG];
	glm::ivec3 seg;
	Tim::Array2D<MapDrawObject*>*dmaps;
	CubeModel *cube;
	Map *map;
	Position *pos;
	glm::ivec3 segsize;
};

#endif /* DISPLAYMAP_H_ */
