/*
 * AudioPlayer.h
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_AUDIOPLAYER_H_
#define SOURCE_CLASS_AUDIO_AUDIOPLAYER_H_


#include <cstdio>
#include <string>
#include <AL/alut.h>
namespace Audio {

class AudioPlayer {
public:
	AudioPlayer();
	AudioPlayer(std::string _audio_name);
	AudioPlayer(ALuint _buffer);
	virtual ~AudioPlayer();
	void play();
	void pause();
	void set_source(std::string _audio_name);
	void set_source(ALuint _buffer);
	void set_loop(bool _loop);
private:
	std::string file_name;
	ALuint buffer;
	ALuint source;
	ALint  state;
	bool is_pause;
	bool is_looping;
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_AUDIOPLAYER_H_ */
