#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCONTROLLER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCONTROLLER_H_

#include "class/controller/Controller.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/ageOfCube/map/attack/Attack.h"
#include "class/game/ageOfCube/map/attack/weapon/WeaponCreator.h"
#include <vector>
namespace AOC {
class AttackCreator;
class AttackController: public Controller ,public Tim::GlobalObject<AttackController>{
public:
	AttackController();
	virtual ~AttackController();
	virtual void update();
	void draw();
	void save(FILE *file);
	void load(FILE *file);
	inline void push(Attack* attack){attacks.push_back(attack);}
	inline void remove(Attack* attack){
		for(unsigned i=0;i<attacks.size();i++){
			if(attacks.at(i)==attack){
				attacks.at(i)=attacks.back();
				attacks.pop_back();
			}
		}
	}
protected:
	std::vector<Attack*>attacks;
	AttackCreator* creator;
	WeaponCreator* weapon_creator;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_ATTACKCONTROLLER_H_ */
