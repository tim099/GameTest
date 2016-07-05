#ifndef SOURCE_CLASS_GAME_CONFIG_H_
#define SOURCE_CLASS_GAME_CONFIG_H_
#include <string>
#include "class/tim/math/vec2.h"
#include "class/tim/globalObject/GlobalObject.h"
class Game;
namespace game {

class Config : public Tim::GlobalObject<Config>{
public:
	Config();
	virtual ~Config();
	void save(std::string path);
	void load(std::string path);

	unsigned shadow_quality;
	bool enable_pssm;

	math::vec2<int> window_size;
	bool full_screen;
};

} /* namespace game */

#endif /* SOURCE_CLASS_GAME_CONFIG_H_ */
