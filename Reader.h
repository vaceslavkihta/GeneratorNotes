#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <memory>

using namespace std;

struct fileDeleter {
	void operator()(ifstream* f) { if (f) f->close(); delete f; }
};

class Reader
{
public:
	Reader(string);
	void read();
	vector<string>& getVec() {
		vector<string>& res = vec;
		return res;
	}

protected:
	vector<string> vec; // расписание
	unique_ptr <ifstream, fileDeleter> file;
};