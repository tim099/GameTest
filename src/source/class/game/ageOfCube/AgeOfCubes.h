/*
 * Age Of Cube version -1.0
 * Copyright (C) 2016, Tim Yeh<tim11251994@gmail.com>
 *
 * This program is free software;
 * you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 */
#ifndef SOURCE_CLASS_GAME_AGEOFCUBES_H_
#define SOURCE_CLASS_GAME_AGEOFCUBES_H_
#include "class/game/Game.h"

#include "class/display/texture/AllTextures.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"

namespace AOC{
class AgeOfCubes : public Game{
public:
	AgeOfCubes();
	virtual ~AgeOfCubes();
private:
	virtual Display::Window* create_window();
	virtual void initialize_game();
	virtual void terminate_game();
	virtual void game_update();


	Display::AllDrawObjects *drawObjects;
	Display::AllTextures* textures;
	Display::AllModelBuffers* modelBuffers;
	//SceneStart *startScene;

};
}
#endif /* SOURCE_CLASS_GAME_AGEOFCUBES_H_ */
