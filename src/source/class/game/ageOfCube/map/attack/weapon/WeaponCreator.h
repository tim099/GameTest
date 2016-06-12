#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPONCREATOR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPONCREATOR_H_
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"
namespace AOC {

class WeaponCreator : public Tim::GlobalObject<WeaponCreator>{
public:
	WeaponCreator();
	virtual ~WeaponCreator();
	Weapon* create(std::string type_name);
protected:
	void push(Weapon* obj);
	Tim::MapContainer<std::string,Weapon>creator;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPONCREATOR_H_ */
