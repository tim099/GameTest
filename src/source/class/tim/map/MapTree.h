#ifndef SOURCE_CLASS_TIM_MAP_MAPTREE_H_
#define SOURCE_CLASS_TIM_MAP_MAPTREE_H_
#include "class/tim/map/MapContainer.h"
namespace Tim {
template <class maptype,class type>
class MapTree {
public:
	MapTree();
	virtual ~MapTree();
	std::string get_name()const;
	void set_name(std::string name);

	type *get(std::string path);

	//push a map into this
	void push_map(maptype* map);

	//remove a map from this
	void remove_map(maptype* map);


	/*
	 * get map by name
	 */
	maptype* get_map(std::string name);
	/*
	 *push a dir into this
	 */
	void push_dir(MapTree *dir);
	/*
	 * get Dir by name
	 */
	MapTree* get_dir(std::string name);
protected:
	Tim::MapContainer<std::string,maptype>maps;
	Tim::MapContainer<std::string,MapTree<maptype,type> >dirs;
	std::string name;
};

} /* namespace Tim */
#include "class/tim/map/MapTree.cpp"
#endif /* SOURCE_CLASS_TIM_MAP_MAPTREE_H_ */
