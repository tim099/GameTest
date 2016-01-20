#ifndef FILE_H_
#define FILE_H_
#include <cstdio>
#include <string>
#include <vector>
#include <dirent.h>
namespace Tim {

class File {
public:
	File();
	virtual ~File();
	static std::vector<std::string> get_all_files(const char* path);
	static bool check_if_file_exist(std::string dir_path,std::string file_name);
	static std::string get_type(const char* path);
	static off_t get_file_size(const char *path);
	static std::string* load_file_to_string(const char* path);
	static char* load_file(const char* path,int &size);
	off_t size;
};

} /* namespace Tim */

#endif /* FILE_H_ */
