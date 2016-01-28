#include "class/game/AgeOfCubes.h"
#include <iostream>
AgeOfCubes::AgeOfCubes() {
	controller_system=0;
	render_thread = 0;
	thread_pool = 0;
	//====================================
	input = 0;
	//====================================
	camera = 0;
	draw = 0;
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
	lightControl = 0;
	renderer = 0;
	render_thread = 0;
	thread_pool = 0;
	render_task = 0;
	startScene=0;
}
void AgeOfCubes::initialize_game(){

	//=============================
	camera = new Camera(glm::vec3(36.0, 24.0, 24.0),
			glm::vec3(34.0, 22.0, 27.0), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);

	textures = new AllTextures("files/script/loadTextureScript/loadAllTexture.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers = new AllModelBuffers("files/script/modelBufferScript/loadAllModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new AllDrawObjects("files/script/drawObjectScript/loadAllDrawObjects.txt");
	drawObjects->register_cur();

	lightControl = new LightControl(120);

	draw->set_camera(camera);
	draw->set_lightControl(lightControl);


	startScene=new SceneStart();
	push_scene(startScene);
}
void AgeOfCubes::terminate_game(){
	//delete in reverse of create order
	std::cout<<"terminate game start"<<std::endl;
	delete lightControl;
	delete drawObjects;
	delete modelBuffers;
	delete textures;
	delete camera;
	//==================

	std::cout<<"terminate game end"<<std::endl;
}
AgeOfCubes::~AgeOfCubes() {

}
Window* AgeOfCubes::create_window(){
	return (new Window(glm::ivec2(1366, 733), "Age of Cube", false)); //must create before any draw obj
}
void AgeOfCubes::game_update(){



}

