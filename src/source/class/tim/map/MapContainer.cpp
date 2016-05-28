#ifndef SOURCE_CLASS_TIM_MAP_MAPCONTAINER_CPP_
#define SOURCE_CLASS_TIM_MAP_MAPCONTAINER_CPP_
#include "class/tim/map/MapContainer.h"
#include <iostream>
namespace Tim {
template<class Key,class Type>
MapContainer<Key,Type>::MapContainer(bool _auto_delete) {
	auto_delete=_auto_delete;
}
template<class Key,class Type>
MapContainer<Key,Type>::~MapContainer() {
	if(auto_delete){
		typename std::map<Key, Type*>::iterator it = map.begin();
		while (it != map.end()) {
			delete (it->second);
			it++;
		}
	}
}
template<class Key,class Type>
void MapContainer<Key,Type>::remove(Key key){
	Type* obj=get(key);
	if(obj){
		map.erase(key);
		if(auto_delete)delete obj;
	}else{
		std::cerr << "MapContainer remove fail key:" << key
				<< " not exist in this MapContainer" << std::endl;
	}
}
template<class Key,class Type>
bool MapContainer<Key,Type>::find(Key key){
	if (map.find(key) == map.end()) {
		return false;
	}
	return true;
}
template<class Key,class Type>
Type* MapContainer<Key,Type>::get(Key key){
	if (map.find(key) == map.end()) {
		std::cerr << "MapContainer key:" << key
				<< " not exist in this MapContainer" << std::endl;
		return 0;
	}
	return map[key];
}

template<class Key,class Type>
void MapContainer<Key,Type>::push(Key key,Type *type){

	if (map.find(key) != map.end()) {
		std::cerr << "MapContainer key:" << key
				<< " already exist in this MapContainer" << std::endl;
		return;
	}
	map[key]=type;
}
} /* namespace Tim */
#endif /* SOURCE_CLASS_TIM_MAP_MAPCONTAINER_CPP_ */
