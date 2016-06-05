/*
 * AllAudioSources.cpp
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#include <iostream>
#include <class/audio/AllAudioSources.h>

namespace Audio {

AllAudioSources::AllAudioSources() {
	// TODO Auto-generated constructor stub
}

AllAudioSources::AllAudioSources(std::string script_path) {
	Load_script(script_path);
}


AllAudioSources::~AllAudioSources() {
	// TODO Auto-generated destructor stub
}

void AllAudioSources::Parse_Script(std::istream &is, std::string &line){
	if (line=="Map:") {
		Parse_map(is);
	}else if(line=="Dir:"){
		Parse_dir(is);
	}
}

void AllAudioSources::Parse_Header(std::istream &is, std::string &line){
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}

void AllAudioSources::Parse_map(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AudioMap* map=new AudioMap(folder_path+scriptPath);
		push_map(map);
	}
}

void AllAudioSources::Parse_dir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllAudioSources* dir=new AllAudioSources(folder_path+scriptPath);
		push_dir(dir);
	}
}

} /* namespace Audio */
