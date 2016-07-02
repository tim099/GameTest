#include "class/tim/string/String.h"
#include "class/tim/math/Math.h"
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
namespace Tim {
String::String() {

}
String::~String() {

}
int String::str_to_int(std::string str){
	int val;
	sscanf(str.c_str(),"%d",&val);
	return val;
}
std::string String::to_string(int num){
	char cnum[100];
	sprintf(cnum,"%d",num);
	return std::string(cnum);
}
std::string String::to_string(double num){
	char cnum[100];
	sprintf(cnum,"%.2lf",num);
	return std::string(cnum);
}
void String::put_back_line(std::istream &is,std::string& line){
	for(unsigned i=0;i<line.size();i++){
		std::cout<<"put_back:"<<line[i]<<std::endl;
		is.putback(line[i]);
	}
	is.putback('\n');
	std::cout<<"put_back finish"<<std::endl;
}
bool String::get_line(std::istream &is,std::string& strline,bool skip_blankline,bool skip_blankspace){
	char line[256];
	if(is.eof())return false;
	if(skip_blankline){
		while(!is.eof()){
			is.getline(line,sizeof(line));
			if(strlen(line)!=0)break;
		}
	}else{
		is.getline(line,sizeof(line));
	}
	strline=std::string(line);
	if(skip_blankspace){
		strline=Tim::String::cut(strline,std::string(" 	"));
	}

	return true;
}
void String::gen_array_num(char *str,int num){
	sprintf(str,"[%d]",num);
}
bool String::within(char c,const std::string& str){
	for(unsigned j=0;j<str.length();j++){
		if(c==str[j])return true;
	}
	return false;
}
void String::split(std::string str,std::string delimiter,std::vector<std::string> &out){
	out.clear();
	unsigned pos=0;
	bool start=false;
	for(unsigned i=0;i<str.size();i++){
		if(start){//start
			if(within(str[i],delimiter)){//find delimiter, out put end!!
				start=false;
				out.push_back(str.substr(pos,i-pos));
			}
		}else{//not start yet
			if(!within(str[i],delimiter)){//char to output
				start=true;
				pos=i;
			}
		}
	}
	if(start){
		out.push_back(str.substr(pos,str.size()-pos));
	}
}
void String::get_between(std::istream &is,std::string& strline,std::string delimiter){
	strline="";
	char c=0;
	while(!within(c,delimiter)){
		is>>c;
	}
	while(true){
		is.get(c);
		if(within(c,delimiter))break;
		strline+=c;
	}
}
std::string String::cut(std::string str,std::string cskip,bool front,bool back){
	unsigned start=0;
	unsigned end=str.size();
	if(front){
		while(start<str.size()){
			if(!within(str[start],cskip))break;//start
			start++;
		}
	}
	if(back){
		while(end>0&&within(str[end-1],cskip)){
			end--;
		}
	}
	return str.substr(start,end-start);
}

}
