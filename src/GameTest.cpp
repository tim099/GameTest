#include "class/test/Test.h"
#include "class/display/texture/image/ImgData.h"
#include "class/display/texture/image/Image.h"

#include "class/tim/math/Vec.h"
#include <iostream>
//#include <cstdio>
//#include <thread>
int main(){
	Test *test=new Test();
	//Test2 *test=new Test2();
	//ImgData<unsigned char>* img=new ImgData<unsigned char>;
	//Test::timer_tic

	//printf("%d\n",test->creat_light());
	test->Mainloop();
	delete test;

    return 0;
}
