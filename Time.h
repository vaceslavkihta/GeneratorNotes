#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <exception>
#include <compare>
#include <ostream>

using std::cout;
using std::endl;
using std::wstring, std::string;
using std::pair, std::make_pair;
using std::wostream;

class Time
{
public:
	Time();
	Time(int, int);
	Time(const pair<int, int>&);
	Time(const Time&);

public:
	void changeMin(int);
	void changeHour(int);
	void restoreTime(int, int);
	void restoreTime(const Time&);
	
public:
	int getHour() const;
	int getMin() const;
	pair<int, int> getTime() const;

public:
	Time operator+(const pair<int, int>&);
	Time operator+(const Time&);
	Time operator+(const int&);

	Time operator-(const pair<int, int>&);
	Time operator-(const Time&);
	Time operator-(const int&);

	Time& operator=(const Time&);
	Time& operator=(pair<int, int>);

	operator pair<int, int>() const;
	explicit operator int() const;

public:
	auto operator<=>(const Time&) const = default;

private:
	pair<int, int> time_;
};

pair<int, int> normalizeTime(const pair<int, int>&);
bool isCorrectlyTime(const pair<int, int>&);

Time& operator+=(Time&, const pair<int, int>&);
Time& operator+=(Time&, const Time&);
Time& operator+=(Time&, const int&);

Time& operator-=(Time&, const pair<int, int>&);
Time& operator-=(Time&, const Time&);
Time& operator-=(Time&, const int&);

wostream& operator<<(wostream&, const Time&);

wstring getTimeStr(const Time&);