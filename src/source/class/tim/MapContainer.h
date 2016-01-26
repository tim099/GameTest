#ifndef SOURCE_CLASS_TIM_MAPCONTAINER_H_
#define SOURCE_CLASS_TIM_MAPCONTAINER_H_
#include <map>
namespace Tim {
template<class Key,class Type>
class MapContainer {
public:
	MapContainer();
	virtual ~MapContainer();
	Type* get(Key key);
	void push(Key key,Type *type);
protected:
	std::map<Key,Type*>map;
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_MAPCONTAINER_H_ */
