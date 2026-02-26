#include "Time.h"

Time::Time() : time_({0, 0}) { ; }
Time::Time(int hour, int minute) : time_({ hour, minute }) { isCorrectlyTime(time_); }
Time::Time(const pair<int, int>& sample): time_(sample) { isCorrectlyTime(time_); }
Time::Time(const Time& other) : time_(other.time_) { isCorrectlyTime(time_); }


void Time::changeHour(int hour) { 
	if (hour < 24) time_.first = hour;
	else { throw std::range_error("void Time::changeHour(int) generate exception std::range_error\nargument too large\n((Time::hours_ += hour (arg)) >= 24)"); }
}
void Time::changeMin(int min) {
	time_.second = min;
}
void Time::restoreTime(int hour, int min) {
	time_ = make_pair(hour, min);	
}
void Time::restoreTime(const Time& oth) { time_ = oth.time_; }

int Time::getHour() const { return time_.first; }
int Time::getMin() const { return time_.second; }
pair<int, int> Time::getTime() const { return time_; }

Time Time::operator+(const pair<int, int>& rhs) {
	
	pair<int, int> res = { time_.first + rhs.first, time_.second + rhs.second };
	if (!isCorrectlyTime(res)) { res = normalizeTime(res); }
	return res;
}
Time Time::operator+(const Time& rhs) {
	return *this + rhs.time_;
}
Time Time::operator+(const int& rhs) {
	return *this + make_pair(0, rhs);
}

Time Time::operator-(const pair<int, int>& rhs) {
	pair<int, int> res;
	int timeInMins = time_.first * 60 + time_.second;
	timeInMins -= rhs.first * 60; timeInMins -= rhs.second;
	return { timeInMins / 60, timeInMins % 60 };
}
Time Time::operator-(const Time& rhs) {
	return *this - rhs.time_;
}
Time Time::operator-(const int& rhs) { return *this - make_pair(0, rhs); }

Time& Time::operator=(const Time& rhs) {
	if (isCorrectlyTime(rhs.time_)) { time_ = rhs.time_; }
	else { time_ = normalizeTime(rhs.time_); }
	return *this;
}
Time& Time::operator=(pair<int, int> rhs) {
	if (isCorrectlyTime(rhs)) { time_ = rhs; }
	else { time_ = normalizeTime(rhs); }
	return *this;
}

Time::operator pair<int, int>() const { return time_; }
Time::operator int() const { return time_.first * 60 + time_.second; }

pair<int, int> normalizeTime(const pair<int, int>& time) {
	int hrsInMin = time.second / 60,
		newHours = time.first + hrsInMin, newMins = time.second % 60;

	return { newHours, newMins };
}
bool isCorrectlyTime(const pair<int, int>& time) {
	int hrsInMin = time.second / 60, newHours = time.first + hrsInMin;

	if (time.first < 0 || time.second < 0) { throw std::range_error("bool isCorrectlyTime(const Time&) genetate std::range_error\n hours_ or min_ have negative values\n Time::hours_ < 0 || Time::min_ < 0"); }
	if (newHours >= 24) { throw std::range_error("bool isCorrectlyTime(const Time&) generated exception\nhours >= 24 (check arguments)"); }
	
	if (time.second < 60) { return true; }
	else { return false; }
}

Time& operator+=(Time& lhs, const pair<int, int>& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}
Time& operator+=(Time& lhs, const Time& rhs) {
	lhs = lhs + rhs;
	return lhs;
}
Time& operator+=(Time& lhs, const int& rhs) {
	return lhs += make_pair(0, rhs);
}

Time& operator-=(Time& lhs, const pair<int, int>& rhs) {
	lhs = lhs - rhs;
	return lhs;
}
Time& operator-=(Time& lhs, const Time& rhs) { lhs = lhs - rhs; return lhs; }
Time& operator-=(Time& lhs, const int& rhs) { lhs = lhs - make_pair(0, rhs); return lhs; }

wostream& operator<<(wostream& s, const Time& time) {
	wstring spaceH = L"", spaceM = L"";
	if (time.getHour() < 10) { spaceH = L"0"; }
	if (time.getMin() < 10) { spaceM = L"0"; }
	return s << spaceH << time.getHour() << L":" << spaceM << time.getMin();
}

wstring getTimeStr(const Time& rhs) {
	wstring res = L"";
	int hours = rhs.getHour(), mins = rhs.getMin();
	if (hours < 10) { res += L"0"; }
	res += std::to_wstring(hours) + L":";

	if (mins < 10) { res += L"0"; }
	res += std::to_wstring(mins);
	return res;
}