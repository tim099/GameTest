/*
 * AudioConfig.cpp
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <class/audio/AudioConfig.h>

namespace Audio {

AudioConfig::AudioConfig() {
	// TODO Auto-generated constructor stub

}

void AudioConfig::audio_init(){
	alutInit(0, NULL);
	alGetError();	// Capture errors
}

void AudioConfig::audio_exit(){
	alutExit();
}

AudioConfig::~AudioConfig() {
	// TODO Auto-generated destructor stub
}

} /* namespace Audio */
