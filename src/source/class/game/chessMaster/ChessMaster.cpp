#include "class/game/chessMaster/ChessMaster.h"
#include "class/game/chessMaster/common.h"
#include "class/game/chessMaster/scene/SceneStart.h"
ChessMaster::ChessMaster() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
}
ChessMaster::~ChessMaster() {

}
Window* ChessMaster::create_window(){
	return (new Window(glm::ivec2(1366, 733), "Chess Master", false));
}
void ChessMaster::initialize_game(){
	textures = new AllTextures(CM::folder_path+"script/texture/Textures.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers = new AllModelBuffers(CM::folder_path+"script/modelbuffer/ModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new AllDrawObjects(CM::folder_path+"script/drawobject/DrawObjects.txt");
	drawObjects->register_cur();
	push_scene(new CM::scene::SceneStart());
}
void ChessMaster::terminate_game(){
	delete textures;
	delete modelBuffers;
	//delete drawObjects;
}
void ChessMaster::game_update(){



}
