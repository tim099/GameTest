#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include <cstring>
namespace Tim {

File::File() {

}
File::~File() {

}
std::vector<std::string> File::get_all_files(const char* path){
	std::vector<std::string>filenames;
	DIR *dir;
	struct dirent *ent;
	dir=opendir(path);
	if (dir) {
		while((ent=readdir(dir))){
			if(strcmp(".",ent->d_name)&&strcmp("..",ent->d_name)){
				filenames.push_back(std::string(ent->d_name));
				//if ent->d_type == 16, ent is a folder
				//printf ("%s,type=%d\n",ent->d_name,ent->d_type);
			}
		}
		closedir(dir);
	}else{
		std::cerr<<"File::get_all_files() can't open :"<<path<<std::endl;
	}
	return filenames;
}


} /* namespace Tim */
