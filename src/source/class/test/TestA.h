#ifndef SOURCE_CLASS_TEST_TESTA_H_
#define SOURCE_CLASS_TEST_TESTA_H_
#include <iostream>
#include <string>
namespace Tim {

class TestA {
public:
	TestA(std::string _name){
		name=_name;
	}
	virtual ~TestA(){
		std::cout<<"TestA::~TestA():"<<name<<std::endl;
	}
	void hi(){
		std::cout<<"hi:"<<name<<std::endl;
	}
	std::string name;
};

} /* namespace Tim */

#endif /* SOURCE_CLASS_TEST_TESTA_H_ */
