/*
 * Age Of Cube version 1.0
 * Copyright (C) 2016, Tim Yeh<tim11251994@gmail.com>
 *
 * This program is free software;
 * you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 */


//#include "class/test/Test.h"

#include <iostream>

//#include <thread>

#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/chessMaster/ChessMaster.h"

#include "class/tim/pointer/smartPointerTest.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
ALuint buffer, source;
void test_al(){
    alutInit(0, NULL);
    alGetError();

    buffer = alutCreateBufferFromFile("files/wave/notitle.wav");//Notitle.wv
    alGenSources(1, &source);
	alSourcei(source,AL_BUFFER, buffer);
    alSourcePlay(source);
}
void test_al_end(){
	alSourcePause(source);
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alutExit();
}
int main(){



	///*

	//while(true){

	test_al();
	AOC::AgeOfCubes* ageOfCubes=new AOC::AgeOfCubes();
	ageOfCubes->initialize();
	ageOfCubes->mainloop();
	delete ageOfCubes;
	test_al_end();


	//}

	//*/

	/*
	//while(true){
	ChessMaster* cm=new ChessMaster();
	cm->initialize();

	cm->mainloop();
	delete cm;
	//}
	*/

	/*
	Test *test=new Test();
	test->Mainloop();

	delete test;
	*/

    return 0;
}
