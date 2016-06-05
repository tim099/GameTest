/*
 * AudioSource.h
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_AUDIOSOURCE_H_
#define SOURCE_CLASS_AUDIO_AUDIOSOURCE_H_


#include <cstdio>
#include <string>
typedef unsigned int ALuint;
namespace Audio {

class AudioSource {
public:
	//AudioSource();
	AudioSource(std::string _file_name);
	virtual ~AudioSource();
	void delete_source();
	inline ALuint get_buffer(){return buffer;};
private:
	std::string file_name;
	ALuint buffer;
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_AUDIOSOURCE_H_ */
