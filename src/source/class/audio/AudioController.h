/*
 * AudioController.h
 *
 *  Created on: 2016¦~6¤ë3¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_AUDIO_AUDIOCONTROLLER_H_
#define SOURCE_CLASS_AUDIO_AUDIOCONTROLLER_H_

#include <vector>
#include "class/tim/globalObject/GlobalObject.h"
#include "class/controller/Controller.h"
#include "class/audio/AudioPlayer.h"

namespace Audio {

class AudioController : public Controller,
						public Tim::GlobalObject<AudioController>
{
public:
	AudioController();
	virtual ~AudioController();
	virtual void update();
private:
	std::vector<AudioPlayer *>audio_players;
};

} /* namespace Audio */

#endif /* SOURCE_CLASS_AUDIO_AUDIOCONTROLLER_H_ */
