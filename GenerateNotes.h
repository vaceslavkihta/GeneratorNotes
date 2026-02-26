#include <vector>
#include <chrono>
#include <fstream>
#include <format>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "Parser.h"

#pragma once

using std::ofstream;
using std::format;

class GenerateNotes {
public:
	GenerateNotes(const string&, const string&); // call Reader::read

	void generate();

private:
	Parser pars;
	string pathToDir;
	vector<Note> notes_;
};

string getTimeTitle();