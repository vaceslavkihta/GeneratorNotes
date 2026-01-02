#include "Time.h"

Time::Time() : _hours(0), _min(0) { ; }
Time::Time(int hour, int minute) :_hours(hour), _min(minute) { isCorrectlyTime(); }
Time::Time(Time& other) :_hours(other._hours), _min(other._min) { ; }
Time::Time(Time&& other) noexcept : _hours(other._hours), _min(other._min){
	other._hours = 0;
	other._min = 0;
}

void Time::changeHour(int hour) { 
	if (hour <= 24) _hours = hour;
	else { throw std::range_error("changeHour(int hour) generate exception std::range_error\nhour не может быть больше 24\n((Time::_hours += hour) >= 24)"); }
}

void Time::changeMin(int min) {
	_min = min;
	isCorrectlyTime();
}

void Time::restoreTime(int min, int hour) {
	if (hour <= 24) _hours = hour;
	else { cout << "hour > 24"; }
	_min = min;
	isCorrectlyTime();
}

void Time::isCorrectlyTime() {
	if (_min >= 60) { 
		_hours++; 
		_min -= 60;
	}
	if (_hours >= 24) { throw std::range_error("isCorrectlyTime(void) generate exception std::range_error\n_hours не может быть больше 24"); }
}

void Time::print() {
	string spaceH, spaceM = "";
	_hours >= 10 ? spaceH = "" : spaceH = "0";
	_min >= 10 ? spaceM = "" : spaceM = "0";
	cout << spaceH << _hours << ":" << spaceM << _min;
}

void Time::operator+=(int mins)
{
	_hours += mins / 60; // hour = 60
	_min += (mins %= 60);
	isCorrectlyTime();
}


int Time::getHour() const { return _hours; }
int Time::getMin() const { return _min; }
pair<int, int> Time::getTime() const { return { _hours, _min }; }

int timeToMins(int hours, int mins) {
	return (mins + hours * 60);
}