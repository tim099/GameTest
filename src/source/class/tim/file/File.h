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
};

} /* namespace Tim */

#endif /* FILE_H_ */
