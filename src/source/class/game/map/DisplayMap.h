#ifndef DISPLAYMAP_H_
#define DISPLAYMAP_H_
#include "class/game/map/MapDrawObject.h"
#include "class/display/model/cube/CubeModel.h"
#include "class/tim/thread/mutex/Mutex.h"

#include <queue>
namespace Tim{
	class ThreadPool;
}
class Map;
class Camera;
class Draw;
class AllTextures;
class Window;
class Position;
class DisplayMap {
public:
	static const int SEG=15;


	DisplayMap(Map *map,Draw *d_obj,AllTextures *textures,Window *window);
	virtual ~DisplayMap();

	void create_map_object(int px,int pz);

	void gen_map_obj(Tim::ThreadPool* threadpool);
	void draw_map(Camera *camera);

	void max_y_alter(int val,Tim::ThreadPool* threadpool);
	void update_map(glm::ivec3 pos);
	Tim::Mutex* createMapObjectMutex;
	int range,max_y;
protected:
	Draw *d_obj;
	MapDrawObject* dmaps[SEG][SEG];
	CubeModel *cube;
	Map *map;
	AllTextures *textures;
	Window *window;
	Position *pos;
	int segsize;
};

#endif /* DISPLAYMAP_H_ */
