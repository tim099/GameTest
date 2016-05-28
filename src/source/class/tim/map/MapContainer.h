#ifndef SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_
#define SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_
#include <map>
/*
 * auto delete object in this map when this object being deleted
 */
namespace Tim {
template<class Key,class Type>
class MapContainer {
public:
	MapContainer(bool auto_delete=true);
	virtual ~MapContainer();
	/*
	 * check if key valid(object inside this map)
	 */
	bool find(Key key);
	Type* get(Key key);
	void push(Key key,Type *type);
	void remove(Key key);
	std::map<Key,Type*>* get_map(){
		return &map;
	}
protected:
	std::map<Key,Type*>map;
	bool auto_delete;
};

} /* namespace Tim */
#include "class/tim/map/MapContainer.cpp"
#endif /* SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_ */
