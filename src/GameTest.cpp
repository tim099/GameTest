#include "class/test/Test.h"
#include "class/display/texture/image/ImgData.h"
#include "class/display/texture/image/Image.h"

#include "class/tim/objectpool/ObjectPoolTest.h"
#include "class/tim/objectpool/ObjPoolTest.h"
#include "class/tim/math/Vec.h"
#include <iostream>

#include <string>
//#include <cstdio>
//#include <thread>
int main(){
	//object_pool_test();
	//obj_pool_test();
	//return 0;
	Test *test=new Test();
	test->Mainloop();

	//Test2 *test=new Test2();

	delete test;
    return 0;
}
