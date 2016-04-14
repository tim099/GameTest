#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARDMCT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARDMCT_H_
#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/chessboard/StepData.h"
#include "class/tim/tree/MCT.h"
#include "class/game/chessMaster/chessboard/StepNode.h"
#include <string>
namespace CM {

class BoardMCT : public Tim::MCT<Step,StepData> {
public:
	BoardMCT();
	virtual ~BoardMCT();
	StepNode* find_and_expand(StepNode *cur,Step step);
	StepNode* find(StepNode *cur,Step step);
	void save(std::string path);
	void load(std::string path);

	StepNode* step_root;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BOARDMCT_H_ */
