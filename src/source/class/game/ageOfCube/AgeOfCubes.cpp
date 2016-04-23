#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/ageOfCube/scene/SceneStart.h"
#include <iostream>
namespace AOC{
AgeOfCubes::AgeOfCubes() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
}
Window* AgeOfCubes::create_window(){
	return (new Window(glm::ivec2(1366, 733), "Age of Cube", false));
	//return (new Window(glm::ivec2(900, 900), "Age of Cube", false));
}
void AgeOfCubes::initialize_game(){

	//============================
	textures = new AllTextures("files/script/loadTextureScript/loadAllTexture.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers = new AllModelBuffers("files/script/modelBufferScript/loadAllModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new AllDrawObjects("files/script/drawObjectScript/loadAllDrawObjects.txt");
	drawObjects->register_cur();

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
