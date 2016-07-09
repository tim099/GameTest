#include "class/game/chessMaster/ChessMaster.h"
#include "class/game/chessMaster/common.h"
#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/scene/ScenePlay.h"
#include "class/game/chessMaster/scene/SceneEdit.h"
ChessMaster::ChessMaster() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
	audioSources=0;
	folder_path=CM::folder_path;
}
ChessMaster::~ChessMaster() {

}
void ChessMaster::initialize_game(){
	textures = new Display::AllTextures(CM::folder_path+"script/texture/Textures.txt");
	textures->register_cur();	//set as cur using textures
	modelBuffers = new Display::AllModelBuffers(CM::folder_path+"script/modelbuffer/ModelBuffers.txt");
	modelBuffers->register_cur();
	drawObjects = new Display::AllDrawObjects(CM::folder_path+"script/drawobject/DrawObjects.txt");
	drawObjects->register_cur();
	audioSources = new Audio::AllAudioSources(CM::folder_path+"/audio/loadAllAudios.txt");
	audioSources->register_cur();
	push_scene(new CM::scene::SceneStart());
}
void ChessMaster::terminate_game(){
	delete textures;
	delete modelBuffers;
	//delete drawObjects;
}
void ChessMaster::game_update(){



}
