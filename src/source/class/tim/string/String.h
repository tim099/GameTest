#ifndef STRING_H_
#define STRING_H_
#include <iostream>
#include <string>
#include <vector>
namespace Tim {
class String {
public:
	String();
	virtual ~String();
	static std::string to_string(int num);
	static bool get_line(std::istream &is,std::string& strline,bool skip_blankline=true,bool skip_blankspace=true);
	static bool within(char c,const std::string& str);
	static void gen_array_num(char *str,int num);
	static std::string cut(std::string str,std::string skip,bool front=true,bool back=true);
	static std::vector<std::string> split(std::string str,std::string delimiter);

};
}
#endif /* STRING_H_ */
