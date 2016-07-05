#include "class/game/Config.h"
#include <iostream>
#include <fstream>
#include "class/tim/string/String.h"
#include "class/display/light/shadow/ShadowData.h"
namespace game {

Config::Config() {
	window_size=math::vec2<int>(1366,733);
	full_screen=false;
	enable_pssm=false;
	shadow_quality=Display::ShadowNormalQuality;
	register_cur();
}
Config::~Config() {

}
void Config::save(std::string path){
	std::filebuf file;
	file.open(path.c_str(), std::ios::out);
	std::ostream os(&file);
	os <<"#Config"<< std::endl;
	os <<"screen_resoultion:"<< std::endl;
	os <<"	"<<window_size.x<<","<<window_size.y<< std::endl;
	if(full_screen)os <<"#full_screen"<< std::endl;

	os <<"shadow_quality:"<< std::endl;
	os <<"	"<<shadow_quality<< std::endl;
	if(enable_pssm)os <<"#enable_pssm"<< std::endl;

	file.close();
}
void Config::load(std::string path){
	std::filebuf file;

	file.open(path.c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "file "<<path<<" not find!!" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;
	if (Tim::String::get_line(is, line, true, true) && line != "#Config") {
		std::cerr << "Load_script fail,not a " << "#Config" << " script:"<< std::endl;
		return;
	}
	while(Tim::String::get_line(is, line, true, true)){
		if(line=="screen_resoultion:"){
			Tim::String::get_line(is, line, true, true);
			std::vector<std::string>strs;
			Tim::String::split(line,",",strs);
			window_size.x=Tim::String::str_to_int(strs.at(0));
			window_size.y=Tim::String::str_to_int(strs.at(1));
		}else if(line=="shadow_quality:"){
			Tim::String::get_line(is, line, true, true);
			shadow_quality=Tim::String::str_to_int(line);
		}else if(line=="#full_screen"){
			full_screen=true;
		}else if(line=="#enable_pssm"){
			enable_pssm=true;
		}
	}

	file.close();
}
} /* namespace game */
