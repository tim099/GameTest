#include "class/test/Test.h"
#include "class/game/AgeOfCubes.h"

#include <iostream>

#include <string>
//#include <cstdio>
//#include <thread>
#include "class/tim/string/String.h"
#include "class/game/AgeOfCubes.h"

int main(){
	//AgeOfCubes* ageOfCubes=new AgeOfCubes();
	//ageOfCubes->initialize();
	//ageOfCubes->terminate();
	//delete ageOfCubes;
	Test *test=new Test();
	test->Mainloop();

	delete test;

    return 0;
}
