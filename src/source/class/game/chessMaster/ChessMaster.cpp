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
	textures = new AllTextures(CM::folder_path+"script/texture/AllTexture.txt");
	textures->register_cur();	//set as cur using textures
	//modelBuffers = new AllModelBuffers(folder_path+"modelBufferScript/loadAllModelBuffers.txt");
	//modelBuffers->register_cur();
	//drawObjects = new AllDrawObjects(folder_path+"drawObjectScript/loadAllDrawObjects.txt");
	//drawObjects->register_cur();
	push_scene(new CM::scene::SceneStart());
}
void ChessMaster::terminate_game(){

}
void ChessMaster::game_update(){



}
