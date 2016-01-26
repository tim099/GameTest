#include "class/tim/MapContainer.h"
#include <iostream>
namespace Tim {
template<class Key,class Type>
MapContainer<Key,Type>::MapContainer() {

}
template<class Key,class Type>
MapContainer<Key,Type>::~MapContainer() {
	typename std::map<Key, Type*>::iterator it = map.begin();
	while (it != map.end()) {
		delete (it->second);
		it++;
	}
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
