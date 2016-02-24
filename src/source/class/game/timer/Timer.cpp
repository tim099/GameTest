#include "class/game/timer/Timer.h"
#include <iostream>
Timer::Timer() {
	second=0,max_second=60;
	minute=0,max_minute=60;
	hour=0,max_hour=24;
	day=0,max_day=30;
	month=0,max_month=12;
	year=0,max_year=999999;
}
Timer::~Timer() {

}
void Timer::second_update(){
	//std::cout<<"sec:"<<second;//<<std::endl;
}
void Timer::minute_update(){
	//std::cout<<"minute:"<<minute<<std::endl;
}
void Timer::hour_update(){
	//std::cout<<"hour:"<<hour<<std::endl;
}
void Timer::day_update(){
	//std::cout<<"day:"<<day<<std::endl;
}
void Timer::month_update(){
	std::cout<<"month:"<<month<<std::endl;
}
void Timer::year_update(){
	std::cout<<"year:"<<year<<std::endl;
}

void Timer::year_tic(){
	year++;
	year_update();
	if(year>=get_max_year()){
		year=0;
	}
}
void Timer::month_tic(){
	month++;
	month_update();
	if(month>=get_max_month()){
		month=0;
		year_tic();
	}
}
void Timer::day_tic(){
	day++;
	day_update();
	if(day>=get_max_day()){
		day=0;
		month_tic();
	}
}
void Timer::hour_tic(){
	hour++;
	hour_update();
	if(hour>=get_max_hour()){
		hour=0;
		day_tic();
	}
}
void Timer::minute_tic(){
	minute++;
	minute_update();
	if(minute>=get_max_minute()){
		minute=0;
		hour_tic();
	}
}
void Timer::second_tic(){
	second++;
	second_update();
	while(second>=get_max_second()){
		second-=get_max_second();
		minute_tic();
	}
}
void Timer::tic(int val){
	for(int i=0;i<val;i++){
		second_tic();
	}
}
