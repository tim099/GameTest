#ifndef SOURCE_CLASS_GAME_ENTITY_COMPONENT_H_
#define SOURCE_CLASS_GAME_ENTITY_COMPONENT_H_

namespace entity {

class Component {
public:
	Component();
	virtual ~Component();

	unsigned id;
};

} /* namespace entity */

#endif /* SOURCE_CLASS_GAME_ENTITY_COMPONENT_H_ */
