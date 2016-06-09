#include "class/game/ageOfCube/field/Field.h"

namespace AOC {

Field::Field() {
	map = new Map();
}
Field::~Field() {
	if(map)delete map;
}
void Field::save(const std::string& path){
	map->save_map(path);
}
void Field::load(const std::string& path){
	map->load_map(path);
}
void Field::update(Timer* timer){
	map->update(timer);
}
void Field::draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool){
	map->draw(draw,camera,threadpool);
}
} /* namespace AOC */
