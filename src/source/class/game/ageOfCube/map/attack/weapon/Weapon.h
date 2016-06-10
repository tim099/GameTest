#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_

namespace AOC {

class Weapon {
public:
	Weapon();
	virtual ~Weapon();
	int attack_timer;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_WEAPON_WEAPON_H_ */
