/*
 * AudioConfig.h
 *
 *  Created on: 2016�~6��3��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_AUDIOCONFIG_H_
#define SOURCE_CLASS_AUDIO_AUDIOCONFIG_H_

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstdio>
#include <string>

namespace Audio {

class AudioConfig {
public:
	AudioConfig();
	virtual ~AudioConfig();
	static void audio_init();
	static void audio_exit();
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_AUDIOCONFIG_H_ */
