#include "class/game/ageOfCube/map/ai/search/SearchTask.h"
#include "class/game/ageOfCube/map/ai/search/Astar.h"
#include <iostream>
namespace AOC {
namespace AI {
namespace search {

SearchTask::SearchTask(Tim::SmartPointer<Finder> _finder) {
	finder=_finder;
	astar=0;
	auto_terminate=true;
}
SearchTask::~SearchTask() {

}
void SearchTask::ExecuteTask(){
	if(finder->stop_search){
		//delete finder;
	}else{
		if(astar){
			astar->search(finder);
		}else{
			std::cerr<<"SearchTask::ExecuteTask() fail,astar not exist!!"<<std::endl;
		}
	}
	finder.get()->search_done=true;
}
} /* namespace search */
} /* namespace AI */
} /* namespace AOC */
