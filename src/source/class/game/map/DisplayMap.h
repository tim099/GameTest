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
class TextureMap;
class Window;
class DisplayMap {
public:
	static const int SEG=10;
	static const double CUBE_SIZE=1.0;

	DisplayMap(Map *map,Draw *d_obj,TextureMap *texmap,Window *window);
	virtual ~DisplayMap();

	void create_map_object(int px,int pz);

	void gen_map_obj(Tim::ThreadPool* threadpool);
	void draw_map(Camera *camera);

	void max_y_alter(int val,Tim::ThreadPool* threadpool);
	void update_map(int x,int y,int z);
	Tim::Mutex* createMapObjectMutex;
	int range,max_y;
protected:
	Draw *d_obj;
	MapDrawObject* dmaps[SEG][SEG];
	CubeModel *cube;
	Map *map;
	TextureMap *texmap;
	Window *window;
	int segsize;
};

#endif /* DISPLAYMAP_H_ */
