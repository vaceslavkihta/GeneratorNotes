#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <exception>

using std::cout;
using std::endl;
using std::string;
using std::pair;

class Time
{
public:
	Time();
	Time(int, int);
	Time(Time&);
	Time(Time&&) noexcept;

public:
	void changeMin(int);
	void changeHour(int);
	void restoreTime(int, int);

public:
	int getHour() const;
	int getMin() const;
	pair<int, int> getTime() const;

public:
	void print();
	void operator+=(int mins);

private:
	int _hours, _min;
	void isCorrectlyTime();
};

int timeToMins(int hours, int mins);