/*
 * Age Of Cube version -1.0
 * Copyright (C) 2016, Tim Yeh<tim11251994@gmail.com>
 *
 * This program is free software;
 * you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 */

#include "class/test/Test.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
//#include <thread>
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/chessMaster/ChessMaster.h"
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/map/cube/Cube.h"
#include "class/game/timer/Timer.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
int main(){

	///*

	//while(true){
	AOC::AgeOfCubes* ageOfCubes=new AOC::AgeOfCubes();
	ageOfCubes->initialize();
	ageOfCubes->mainloop();
	delete ageOfCubes;
	//}

	//*/
	/*
	//while(true){
	ChessMaster* cm=new ChessMaster();
	cm->initialize();

	cm->mainloop();
	delete cm;
	//}
	//*/

	/*
	Test *test=new Test();
	test->Mainloop();

	delete test;
	*/

    return 0;
}
