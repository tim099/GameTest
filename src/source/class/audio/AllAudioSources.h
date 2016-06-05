/*
 * AllAudioSources.h
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_ALLAUDIOSOURCES_H_
#define SOURCE_CLASS_AUDIO_ALLAUDIOSOURCES_H_

#include "class/audio/AudioSource.h"
#include "class/audio/AudioMap.h"
#include "class/tim/map/MapTree.h"
#include "class/tim/globalObject/GlobalObject.h"

namespace Audio {

class AllAudioSources : public Tim::MapTree<AudioMap, AudioSource>,
	public Tim::GlobalObject<AllAudioSources>,
	public Tim::Parser {
public:
	AllAudioSources();
	AllAudioSources(std::string script_path);
	virtual ~AllAudioSources();
protected:
	virtual inline std::string Script_name() const {
		return "#LOAD_ALL_AUDIOSOURCES_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is, std::string &line);
	virtual void Parse_Header(std::istream &is, std::string &line);
	virtual void Parse_map(std::istream &is);
	virtual void Parse_dir(std::istream &is);
	std::string folder_path;
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_ALLAUDIOSOURCES_H_ */
