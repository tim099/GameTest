#include "class/game/ageOfCube/map/ai/search/Finder.h"
#include "class/game/ageOfCube/map/Map.h"
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
double Finder::get_double_size(){
	return (get_size()*Map::CUBE_SIZE);
}
void Finder::save(FILE* file){
	fprintf(file,"%d %d %d %d %d\n",find,stop_search,search_done,
			min_search_times,max_search_times);
	save_finder(file);
}
void Finder::load(FILE* file){
	int tmp_find,tmp_search,tmp_done;
	fscanf(file,"%d %d %d %d %d\n",&tmp_find,&tmp_search,&tmp_done,
			&min_search_times,&max_search_times);
	if(tmp_find)find=true;
	else find=false;
	if(tmp_search)stop_search=true;
	else stop_search=false;
	if(tmp_done)search_done=true;
	else search_done=false;
	load_finder(file);
}


}
}
} /* namespace AI */
