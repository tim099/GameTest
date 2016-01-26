#ifndef SOURCE_CLASS_TIM_PARSER_PARSER_H_
#define SOURCE_CLASS_TIM_PARSER_PARSER_H_
#include <iostream>
#include <string>
namespace Tim {

class Parser {
public:
	Parser();
	virtual ~Parser();
	void Load_script(std::string script_path);
	void Save_script(std::string script_path);
protected:
	virtual std::string Script_name()const=0;
	void Load_Header(std::istream &is);
	void Save_Header(std::ostream &os);

	void Parse(std::istream &is);
	void Parse(std::ostream &os);
	virtual void Parse_Script(std::istream &is,std::string &line)=0;
	virtual void Parse_Header(std::istream &is,std::string &line)=0;
	virtual void Parse_Script(std::ostream &os);
	virtual void Parse_Header(std::ostream &os);
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TIM_PARSER_PARSER_H_ */
