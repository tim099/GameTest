#ifndef SOURCE_CLASS_GAME_TIMER_TIMER_H_
#define SOURCE_CLASS_GAME_TIMER_TIMER_H_

class Timer {
public:
	Timer();
	virtual ~Timer();
	void tic(int val);


	inline int get_max_second()const{
		return max_second;
	}
	inline int get_max_minute()const{
		return max_minute;
	}
	inline int get_max_hour()const{
		return max_hour;
	}
	inline int get_max_day()const{
		return max_day;
	}
	inline int get_max_month()const{
		return max_month;
	}
	inline int get_max_year()const{
		return max_year;
	}

	inline double get_hour()const{
		return hour+((double)get_minute())/max_minute;
	}
	inline double get_minute()const{
		return minute+get_second()/max_second;
	}
	inline double get_second()const{
		return (double)second;
	}
	inline Timer& operator=(const Timer& timer){
		second=timer.second,max_second=timer.max_second;
		minute=timer.minute,max_minute=timer.max_minute;
		hour=timer.hour,max_hour=timer.max_hour;
		day=timer.day,max_day=timer.max_day;
		month=timer.month,max_month=timer.max_month;
		year=timer.year,max_year=timer.max_year;
		return *this;
	}
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
protected:
	void second_tic();
	void minute_tic();
	void hour_tic();
	void day_tic();
	void month_tic();
	void year_tic();

	virtual void second_update();
	virtual void minute_update();
	virtual void hour_update();
	virtual void day_update();
	virtual void month_update();
	virtual void year_update();
	int max_second;
	int max_minute;
	int max_hour;
	int max_day;
	int max_month;
	int max_year;
};

#endif /* SOURCE_CLASS_GAME_TIMER_TIMER_H_ */
