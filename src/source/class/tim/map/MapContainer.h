#ifndef SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_
#define SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_
#include <map>
/*
 * auto delete object in this map
 */
namespace Tim {
template<class Key,class Type>
class MapContainer {
public:
	MapContainer();
	virtual ~MapContainer();
	/*
	 * check if key valid(object inside this map)
	 */
	bool find(Key key);
	Type* get(Key key);
	void push(Key key,Type *type);
	void remove(Key key);
protected:
	std::map<Key,Type*>map;
};

} /* namespace Tim */
#include "class/tim/map/MapContainer.cpp"
#endif /* SOURCE_CLASS_TIM_MAP_MAPCONTAINER_H_ */
