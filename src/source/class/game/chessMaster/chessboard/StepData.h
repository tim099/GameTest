#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPDATA_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPDATA_H_
#include <cstdio>
namespace CM {

class StepData {
public:
	StepData();
	virtual ~StepData();
	void save(FILE * file);
	void load(FILE * file);

	int wins,simulations;
	//int score,depth;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_STEPDATA_H_ */
