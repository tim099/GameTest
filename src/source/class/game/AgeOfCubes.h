#ifndef SOURCE_CLASS_GAME_AGEOFCUBES_H_
#define SOURCE_CLASS_GAME_AGEOFCUBES_H_
#include "class/game/Game.h"


class AgeOfCubes : public Game{
public:
	AgeOfCubes();
	virtual ~AgeOfCubes();
	void initialize();
	void Mainloop();
protected:

};

#endif /* SOURCE_CLASS_GAME_AGEOFCUBES_H_ */
