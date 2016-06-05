#include "class/game/ageOfCube/map/ai/search/Finder.h"
namespace AOC {
namespace AI {
namespace search{
Finder::Finder() {
	find=false;
	stop_search=false;
	search_done=false;
	min_search_times=3000;
	max_search_times=10000;
}
Finder::~Finder() {

}
}
}
} /* namespace AI */
