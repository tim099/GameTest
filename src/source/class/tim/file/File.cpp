#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include "sys/stat.h"
#include <cstdio>
#include <cstring>

namespace Tim {

File::File() {
	size = 0;
	data = 0;
	read_at = 0;
}
File::~File() {
	if (data)
		delete[] data;
}
bool File::delete_file(std::string file_path){
	if(!remove(file_path.c_str())){
		return true;
	}else{
		std::cerr<<"File::delete_file:"<<file_path<<"fail"<<std::endl;
	}
	return false;
}
std::string File::get_type(const char* path) {
	char path_buf[100];
	memcpy(path_buf, path, sizeof(char) * strlen(path));
	path_buf[strlen(path)] = 0;

	char* pch = strtok(path_buf, ".");
	pch = strtok(NULL, ".");
	return std::string(pch);
}
std::vector<std::string> File::get_all_files(std::string path) {
	std::vector<std::string> filenames;
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());
	if (dir) {
		while ((ent = readdir(dir))) {
			if (strcmp(".", ent->d_name) && strcmp("..", ent->d_name)) {
				if(ent->d_type==0){//if type==0 then ent is a file
					filenames.push_back(std::string(ent->d_name));
				}
				//if ent->d_type == 16, ent is a folder
				//printf ("%s,type=%d\n",ent->d_name,ent->d_type);
			}
		}
		closedir(dir);
	} else {
		std::cerr << "File::get_all_files() can't open :" << path << std::endl;
	}
	return filenames;
}
std::vector<std::string> File::get_all_dirs(std::string path) {
	std::vector<std::string> dirnames;
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());
	if (dir) {
		while ((ent = readdir(dir))) {
			if (strcmp(".", ent->d_name) && strcmp("..", ent->d_name)) {
				if(ent->d_type==16){//if type==0 then ent is a file
					dirnames.push_back(std::string(ent->d_name));
				}
				//if ent->d_type == 16, ent is a folder
				//printf ("%s,type=%d\n",ent->d_name,ent->d_type);
			}
		}
		closedir(dir);
	} else {
		std::cerr << "File::get_all_files() can't open :" << path << std::endl;
	}
	return dirnames;
}
bool File::check_if_file_exist(std::string dir_path, std::string file_name) {
	std::vector<std::string> files = get_all_files(dir_path.c_str());
	for (unsigned i = 0; i < files.size(); i++) {
		if (files.at(i) == file_name) {
			return true;
		}
	}
	return false;
}
bool File::check_if_file_exist(std::string file_path){
	struct stat st;
	if(stat(file_path.c_str(), &st)==0){
		return true;
	}
	return false;
}
off_t File::get_file_size(const char *path) {
	struct stat st;
	stat(path, &st);
	return st.st_size;
}
void File::load(const char* path) {
	file_path = path;
	read_at = 0;
	if (data){
		delete[] data;
	}
	data = load_file(path,size);
}
char* File::load_file(const char* path, off_t &size) {
	size = get_file_size(path);
	FILE* file = fopen(path, "rb");				//read binary
	char *buffer = new char[size];
	fread(buffer, sizeof(char), size, file);
	fclose(file);
	return buffer;
}
int File::myfscanf_str(char *buffer){
	if(read_at>=size-1)return 0;

	int delta;
	sscanf(data+read_at,"%s%n",buffer,&delta);//,&delta
	read_at+=delta;
	if(read_at>=size-1)return 0;
	return delta;
}
/*
int File::myfscanf(const char *format,...){
	va_list args;
	va_start(args,format);
	int delta;
	std::string my_format=format;
	my_format+="%n";
	_myfscanf(my_format.c_str(),args,&delta);
	va_end(args);
	read_at+=delta;
	return delta;
}
*/
std::string* File::load_file_to_string(const char* path) {
	off_t size;
	char *buffer = load_file(path, size);
	std::string *data = new std::string(buffer);
	delete buffer;
	return data;
}

} /* namespace Tim */
