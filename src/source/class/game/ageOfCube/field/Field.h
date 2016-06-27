#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/attack/AttackController.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/entity/EntityController.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include "class/game/timer/Timer.h"
#include "class/display/light/LightControl.h"
namespace physic{
	class RigidBodyController;
}
namespace AOC {

namespace AI{
namespace search{
	class Astar;
}
}
class Field {
public:
	Field();
	virtual ~Field();
	void save(const std::string& path);
	void load(const std::string& path);
	void update();
	void draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool);
	void draw_back_ground();
	physic::RigidBodyController* rigid_body_controller;
	AttackController* attack_controller;
	UnitController* unit_controller;
	PlayerController *player_controller;
	entity::EntityController* entity_controller;
	Timer timer;
	math::Position galaxy_pos_o;
	math::Position galaxy_pos;

	Display::ParallelLight *sun_light;
	glm::vec3 sun_col_1,sun_col_2,sun_pos;

	AI::search::Astar* astar;
	Map *map;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_FIELD_H_ */
