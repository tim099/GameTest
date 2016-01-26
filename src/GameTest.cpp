#include "class/test/Test.h"
#include "class/game/AgeOfCubes.h"

#include <iostream>

#include <string>
//#include <cstdio>
//#include <thread>
#include "class/tim/string/String.h"
#include "class/game/AgeOfCubes.h"
int main(){
	//AgeOfCubes* ageofcubes=new AgeOfCubes();

	Test *test=new Test();
	test->Mainloop();

	delete test;

    return 0;
}
