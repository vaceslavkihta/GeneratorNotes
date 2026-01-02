#include "Reader.h"

Reader::Reader(string path){ file->open(path); }
void Reader::read() {
	string line;
	while (getline(*file, line)) {
		if (line != "")
		vec.push_back(line);
	}
}