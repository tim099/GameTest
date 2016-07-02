#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/ageOfCube/scene/SceneStart.h"

#include <iostream>
namespace AOC{
AgeOfCubes::AgeOfCubes() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
	audioSources = 0;
	folder_path="files/AgeOfCube/";
}
void AgeOfCubes::initialize_game(){

	//============================
	textures = new Display::AllTextures(folder_path+"texture/script/loadAllTexture.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers=new Display::AllModelBuffers(folder_path+"/models/script/loadAllModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new Display::AllDrawObjects(folder_path+"/drawObject/loadAllDrawObjects.txt");
	drawObjects->register_cur();

	audioSources = new Audio::AllAudioSources(folder_path+"/audio/loadAllAudios.txt");
	audioSources->register_cur();

	push_scene(new AOC::SceneStart());
}
AgeOfCubes::~AgeOfCubes() {
	//all handle by AgeOfCubes::terminate_game()
}
void AgeOfCubes::terminate_game(){
	//delete in reverse of create order
	std::cout<<"terminate game start"<<std::endl;
	delete audioSources;
	delete drawObjects;
	delete modelBuffers;
	delete textures;
	//==================

	std::cout<<"terminate game end"<<std::endl;
}
void AgeOfCubes::game_update(){



}
}
