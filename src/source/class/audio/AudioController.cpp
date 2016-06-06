//Author: LukeWu
#include "class/audio/AudioController.h"
#include "class/audio/AudioConfig.h"
#include <iostream>
namespace Audio {

AudioController::AudioController() {
	Audio::AudioConfig::audio_init();
	player_pool=new Tim::ObjPool<AudioPlayer>(10);


	register_cur();
}
AudioController::~AudioController() {
	delete player_pool;

	Audio::AudioConfig::audio_exit();
}
void AudioController::play(std::string name,double volume){
	AudioPlayer* player=player_pool->create();
	player->init();
	player->set_source(name);
	player->set_volume(volume);
	player->play();
	auto_players.push_back(player);
}
void AudioController::update(){
	AudioPlayer* player;
	for(unsigned i=0;i<auto_players.size();i++){
		player=auto_players.at(i);
		if(!player->playing()){
			//std::cout<<"AudioController::update() free player"<<std::endl;
			player_pool->free(player);
			auto_players.at(i)=auto_players.back();
			auto_players.pop_back();
		}
	}
	//std::cout<<"AudioController::update()"<<std::endl;
}

} /* namespace Audio */
