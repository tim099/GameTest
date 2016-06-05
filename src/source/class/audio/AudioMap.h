/*
 * AudioMap.h
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_AUDIOMAP_H_
#define SOURCE_CLASS_AUDIO_AUDIOMAP_H_

#include "class/audio/AudioSource.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/parser/Parser.h"

namespace Audio {

class AudioMap : public Tim::Parser{
public:
	AudioMap();
	AudioMap(std::string script_path);
	virtual ~AudioMap();
	std::string get_name()const;
	void set_name(std::string name);
	void push(std::string name,AudioSource* obj);
	AudioSource* get(std::string name);

protected:
	virtual inline std::string Script_name()const{
		return "#LOAD_AUDIOMAP_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Header(std::istream &is,std::string &line);
	void Parse_Audio(std::istream &is);
	Tim::MapContainer<std::string,AudioSource>audios;
	std::string name;
	std::string folder_path;
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_AUDIOMAP_H_ */
