/*
 * AudioPlayer.cpp
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/audio/AudioPlayer.h"
#include "class/audio/AllAudioSources.h"
#include <AL/al.h>
#include <AL/alc.h>

namespace Audio {

AudioPlayer::AudioPlayer() {
	buffer = 0;
	source = 0;
	state = 0;
	init();
}
AudioPlayer::AudioPlayer(ALuint _buffer){
	buffer = 0;
	source = 0;
	state = 0;
	init();
	set_source(_buffer);
}
AudioPlayer::AudioPlayer(std::string _audio_name){
	//std::cout<<"AudioPlayer::AudioPlayer(std::string _audio_name)"<<std::endl;
	source = 0;
	state = 0;
	init();
	//alSourcei(source, AL_BUFFER, buffer);
	set_source(_audio_name);
	//std::cout<<"audio player source = "<<source<<" buffer = "<<buffer<<std::endl;
}
AudioPlayer::AudioPlayer(const AudioPlayer &that){
	source = 0;
	state = 0;
	init();
	buffer=that.buffer;
	//alSourcei(source, AL_BUFFER, buffer);
}
AudioPlayer& AudioPlayer::operator=(const AudioPlayer &that){
	set_source(that.buffer);
	return *this;
}
void AudioPlayer::init(){
	is_pause = false;
	is_looping = false;

	if(!source)alGenSources(1, &source);

	set_volume(1.0);
}
AudioPlayer::~AudioPlayer() {
	pause();
	if(source)alDeleteSources(1, &source);
}
void AudioPlayer::play(){
	//std::cout<<"play "<<source<<std::endl;
	alSourcePlay(source);
}
ALuint AudioPlayer::get_state(){
	alGetSourcei(source,AL_SOURCE_STATE,&state);
	return state;
}
bool AudioPlayer::playing(){
	if(get_state()==AL_PLAYING){
		return true;
	}
	return false;
}
void AudioPlayer::pause(){
	alSourcePause(source);
}
void AudioPlayer::set_volume(float _volume){
	volume=_volume;
	alSourcef(source,AL_GAIN,volume);
}
void AudioPlayer::set_loop(bool _loop){
	is_looping = _loop;
	if(is_looping){
		alSourcei(source, AL_LOOPING, 1);
	}
	else{
		alSourcei(source, AL_LOOPING, 0);
	}
}
void AudioPlayer::set_source(std::string _audio_name){
	set_source(AllAudioSources::get_cur_object()->get(_audio_name)->get_buffer());
}
void AudioPlayer::set_source(ALuint _buffer){
	buffer = _buffer;
	if(buffer){
		alSourcei(source, AL_BUFFER, buffer);
	}

}

} /* namespace Audio */
