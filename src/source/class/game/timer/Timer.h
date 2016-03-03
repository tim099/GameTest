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
	int second,max_second;
	int minute,max_minute;
	int hour,max_hour;
	int day,max_day;
	int month,max_month;
	int year,max_year;
};

#endif /* SOURCE_CLASS_GAME_TIMER_TIMER_H_ */
