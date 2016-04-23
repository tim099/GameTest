#ifndef SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPECREATOR_H_
#define SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPECREATOR_H_
#include "class/game/map/landscape/Landscape.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
#include "class/tim/globalObject/GlobalObject.h"
class LandscapeCreator :public Tim::GlobalObject<LandscapeCreator>{
	//: public Tim::Singleton<LandscapeCreator>
public:
	LandscapeCreator();
	virtual ~LandscapeCreator();
	Landscape* create(std::string type_name);
protected:
	void push(Landscape* obj);
	Tim::MapContainer<std::string,Landscape>creator;
};

#endif /* SOURCE_CLASS_GAME_MAP_LANDSCAPE_LANDSCAPECREATOR_H_ */
