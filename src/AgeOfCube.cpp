#include "class/test/Test.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
//#include <cstdio>
//#include <thread>
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/tim/string/String.h"
#include <map>
int main(){
	///*
	AgeOfCubes* ageOfCubes=new AgeOfCubes();
	ageOfCubes->initialize();

	ageOfCubes->mainloop();
	delete ageOfCubes;
	//*/
	/*
	Test *test=new Test();
	test->Mainloop();

	delete test;
	*/
    return 0;
}
