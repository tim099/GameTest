/*
 * AudioMap.cpp
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/audio/AudioMap.h"
#include "class/tim/string/String.h"

namespace Audio {

AudioMap::AudioMap() {
	// TODO Auto-generated constructor stub

}

AudioMap::AudioMap(std::string script_path){
	//std::cout<<"new audio map : "<<script_path<<std::endl;
	Load_script(script_path);
}

AudioMap::~AudioMap() {
	// TODO Auto-generated destructor stub
}

std::string AudioMap::get_name()const{
	return name;
}

void AudioMap::set_name(std::string _name){
	name = _name;
}

void AudioMap::push(std::string name,AudioSource* obj){
	audios.push(name,obj);
}

AudioSource* AudioMap::get(std::string name){
	return audios.get(name);
}

void AudioMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="AudioSource:"){
		Parse_Audio(is);
	}
}

void AudioMap::Parse_Header(std::istream &is,std::string &line){
	if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}

void AudioMap::Parse_Audio(std::istream &is){
	std::string line;
	std::string audio_name;

	while(Tim::String::get_line(is, line, true, true)){
		if(line=="#load_end"){
			AudioSource* loaded_audio=new AudioSource(folder_path+audio_name);
			//std::cout<<"name : "<<audio_name<<std::endl;
			push(audio_name, loaded_audio);
			break;
		}else if(line=="Name:"){
			Tim::String::get_line(is, audio_name, true, true);
		}
	}
}


} /* namespace Audio */
