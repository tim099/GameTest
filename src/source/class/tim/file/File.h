#ifndef FILE_H_
#define FILE_H_
#include <cstdio>
#include <string>
#include <vector>
#include <dirent.h>
#include <cstdarg>
namespace Tim {

class File {
public:
	File();
	virtual ~File();
	static std::vector<std::string> get_all_files(std::string path);
	static std::vector<std::string> get_all_dirs(std::string path);
	static bool check_if_file_exist(std::string dir_path,std::string file_name);
	static bool check_if_file_exist(std::string file_path);
	static bool delete_file(std::string file_path);

	static std::string get_type(const char* path);
	static off_t get_file_size(const char *path);
	static std::string* load_file_to_string(const char* path);
	static char* load_file(const char* path,off_t &size);
	void load(const char* path);
	/*
	 * scan a single string from file
	 */
	int myfscanf_str(char *buffer);
	//int myfscanf(const char *format,...);
	off_t read_at;
	off_t size;
	char *data;
	std::string file_path;
protected:

};

} /* namespace Tim */

#endif /* FILE_H_ */
