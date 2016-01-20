#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include "sys/stat.h"
#include <cstring>
namespace Tim {

File::File() {
	size=0;
}
File::~File() {

}
std::string File::get_type(const char* path){
	char path_buf[100];
	memcpy(path_buf, path, sizeof(char) * strlen(path));
	path_buf[strlen(path)] = 0;

	char* pch = strtok(path_buf, ".");
	pch = strtok(NULL, ".");
	return std::string(pch);
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
bool File::check_if_file_exist(std::string dir_path,std::string file_name){
	std::vector<std::string> files=get_all_files(dir_path.c_str());
	for(unsigned i=0;i<files.size();i++){
		if(files.at(i)==file_name){
			return true;
		}
	}
	return false;
}
off_t File::get_file_size(const char *path) {
	struct stat st;
	stat(path, &st);
	return st.st_size;
}
char* File::load_file(const char* path,int &size){
	size=get_file_size(path);
	FILE* file=fopen(path,"rb");//read binary
	char *buffer=new char[size];
	fread(buffer,sizeof(char),size,file);

	return buffer;
}
std::string* File::load_file_to_string(const char* path){
	int size;
	char *buffer=load_file(path,size);
	std::string *data=new std::string(buffer);
	delete buffer;
	return data;
}

} /* namespace Tim */
