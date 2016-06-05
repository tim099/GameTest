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
	is_pause = false;
	is_looping=false;
	alGenSources(1, &source);
}

AudioPlayer::AudioPlayer(ALuint _buffer){
	buffer = _buffer;
	source = 0;
	state = 0;
	is_pause = false;
	is_looping=false;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
}

AudioPlayer::AudioPlayer(std::string _audio_name){
	buffer = AllAudioSources::get_cur_object()->get(_audio_name)->get_buffer();
	source = 1;
	state = 0;
	is_pause = false;
	is_looping = false;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	std::cout<<"audio player source = "<<source<<" buffer = "<<buffer<<std::endl;
}

AudioPlayer::~AudioPlayer() {
	alSourcePause(source);
    alDeleteSources(1, &source);
}
void AudioPlayer::play(){
	std::cout<<"play "<<source<<std::endl;
	alSourcePlay(source);
}

void AudioPlayer::pause(){
	alSourcePause(source);
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
	ALuint _buffer=AllAudioSources::get_cur_object()->get(_audio_name)->get_buffer();
	set_source(_buffer);
}
void AudioPlayer::set_source(ALuint _buffer){
	buffer = _buffer;
	alSourcei(source, AL_BUFFER, buffer);
}

} /* namespace Audio */
