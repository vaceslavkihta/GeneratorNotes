#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <memory>
#include "Time.h"
#include "Note.h"

using namespace std;

class Parser
{
public:
	Parser(const string& path) :file_(make_unique<ifstream>(path)) {
		if (!file_) { throw std::runtime_error("file did not oppened"); }
		fillLessonsSchd();
		fillSchdVec();
	}
	void fillLessonsSchd();
	void fillSchdVec();
	vector<Note> parseLessons();
	void createOthNotes();
	void createSchdFstLessn(const Note&);
	void createSchdOthLessns(const Note&);

private:
	unordered_map<int, pair<Time, Time>> lessonsSchedule_;
	unique_ptr<ifstream> file_;
	vector<string> schdVec_,
		schdOnFstLessn_ = { "Путь в колледж", "У братков", "Путь домой + обед", "Полезное время" },
		schdOnOthLessns_ = { "Полезное время", "Обед", "Путь в колледж", "Путь домой + ужин" };
	vector<Note> edNotes_, notes_;
};

string dateFromStr(const string&);
pair<int, int> timeFromStr(const string&);
string getTitle(const string&);
Time castTimeToZeroMins(const Time&);