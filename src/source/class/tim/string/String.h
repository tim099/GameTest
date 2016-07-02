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
	static std::string to_string(double num);
	static int str_to_int(std::string str);

	static bool get_line(std::istream &is,std::string& strline,bool skip_blankline=true,bool skip_blankspace=true);
	static void put_back_line(std::istream &is,std::string& line);

	static void get_between(std::istream &is,std::string& strline,std::string delimiter);
	static bool within(char c,const std::string& str);
	static void gen_array_num(char *str,int num);
	static std::string cut(std::string str,std::string skip,bool front=true,bool back=true);

	/*
	 * split the input string by delimiter,
	 * delimiters can compose by several char(each char is a delimiter
	 */
	static void split(std::string str,std::string delimiter,std::vector<std::string> &out);

};
}
#endif /* STRING_H_ */
