#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_
#include "class/game/ageOfCube/map/Map.h"
namespace AOC {

class Field {
public:
	Field();
	virtual ~Field();
	void save(const std::string& path);
	void load(const std::string& path);
	void update(Timer* timer);
	void draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool);
	Map *map;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_ */
