#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPNODE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPNODE_H_

#include "class/tim/tree/Node.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/chessboard/StepData.h"
namespace CM {

class StepNode: public Tim::Node<Step,StepData> {
public:
	StepNode();
	StepNode(Step key,StepData data);
	virtual ~StepNode();
	void save(FILE * file);
	void load(FILE * file);
protected:
	void save_children(FILE * file);
	void load_children(FILE * file);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPNODE_H_ */
