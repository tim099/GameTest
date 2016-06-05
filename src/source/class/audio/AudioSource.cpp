/*
 * AudioSource.cpp
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
#include "class/audio/AudioSource.h"

namespace Audio {
/*
AudioSource::AudioSource() {
	// TODO Auto-generated constructor stub

}*/

AudioSource::AudioSource(std::string _file_name) {
	file_name = _file_name;
	std::cout<<"create buffer : "<<file_name<<std::endl;
	buffer = alutCreateBufferFromFile(file_name.c_str());
	if(buffer == AL_NONE){
		std::cout<<"audio source name : "<<file_name<<" create failed !"<<std::endl;
	}
	else{
		std::cout<<"audio source name : "<<file_name<<" buffer = "<<buffer<<std::endl;
	}
}


void AudioSource::delete_source(){
	alDeleteBuffers(1, &buffer);
}

AudioSource::~AudioSource() {
	// TODO Auto-generated destructor stub
}

} /* namespace Audio */
