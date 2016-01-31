#include "class/tim/parser/Parser.h"
#include "class/tim/string/String.h"
#include <fstream>
namespace Tim {

Parser::Parser() {

}
Parser::~Parser() {

}
void Parser::Parse(std::istream &is) {
	std::string line;
	Load_Header(is);
	while (!is.eof()) {
		Tim::String::get_line(is, line, true, true);
		if (line == "#END") {
			break;
		} else {
			Parse_Script(is, line);
		}
	}
}
void Parser::Parse(std::ostream &os) {
	Save_Header(os);
	Parse_Script(os);
	os << "#END" << std::endl;
}
void Parser::Load_script(std::string script_path) {
	std::filebuf file;

	file.open(script_path.c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Parser::Load_script load fail,file:" << script_path
				<< " open fail" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;
	if (Tim::String::get_line(is, line, true, true) && line != Script_name()) {
		std::cerr << "Load_script fail,not a " << Script_name() << " script:"
				<< script_path << std::endl;
		return;
	}
	Parse(is);
	file.close();
}
void Parser::Save_script(std::string script_path) {
	std::filebuf file;
	file.open(script_path.c_str(), std::ios::out);
	std::ostream os(&file);
	os << Script_name() << std::endl;
	Parse(os);
	file.close();
}
void Parser::Save_Header(std::ostream &os) {
	os << "#HEADER" << std::endl;
	Parse_Header(os);
	os << "#HEADER_END" << std::endl;
}
void Parser::Load_Header(std::istream &is) {
	std::string line;
	if (Tim::String::get_line(is, line, true, true) && line != "#HEADER") {
		std::cerr << "TextureMap::Load_script fail,No Header!!" << line
				<< std::endl;
		return;
	}
	while (Tim::String::get_line(is, line, true, true)) {
		if (line == "#HEADER_END") {
			break;
		} else if (line.substr(0, 1) == "//") { //do nothing

		} else {
			Parse_Header(is, line);
		}
	}
}
void Parser::Parse_Script(std::ostream &os) {
	os << "#Parser::Parse_Script not implement yet" << std::endl;
}
void Parser::Parse_Header(std::ostream &os) {
	os << "#Parser::Parse_Header not implement yet" << std::endl;
}
} /* namespace Tim */
