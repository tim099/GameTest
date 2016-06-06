#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/ageOfCube/scene/SceneStart.h"

#include <iostream>
namespace AOC{
AgeOfCubes::AgeOfCubes() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
	audioSources = 0;
}
/*
Display::Window* AgeOfCubes::create_window(){
	return (new Display::Window(glm::ivec2(1366, 733), "Age of Cube", false));
	//return (new Window(glm::ivec2(900, 900), "Age of Cube", false));
}
*/
void AgeOfCubes::initialize_game(){

	//============================
	textures = new Display::AllTextures("files/AgeOfCube/texture/script/loadAllTexture.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers=new Display::AllModelBuffers("files/AgeOfCube/models/script/loadAllModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new Display::AllDrawObjects("files/AgeOfCube/drawObject/loadAllDrawObjects.txt");
	drawObjects->register_cur();

	audioSources = new Audio::AllAudioSources("files/AgeOfCube/audio/loadAllAudios.txt");
	audioSources->register_cur();

	push_scene(new AOC::SceneStart());
}
AgeOfCubes::~AgeOfCubes() {
	//all handle by AgeOfCubes::terminate_game()
}
void AgeOfCubes::terminate_game(){
	//delete in reverse of create order
	std::cout<<"terminate game start"<<std::endl;
	delete drawObjects;
	delete modelBuffers;
	delete textures;
	//==================

	std::cout<<"terminate game end"<<std::endl;
}
void AgeOfCubes::game_update(){



}
}
