#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <memory>
#include <codecvt>
#include <locale>
#include "Time.h"
#include "Note.h"

using namespace std;

class Parser
{
public:
	Parser(const string& path);

	void parsing() {
		parseLessons();
		createOthNotes();
	}

	vector<Note> getNotes() { return notes_; }
	vector<Note> getEdNotes() { return edNotes_; }

	

private:
	unordered_map<int, pair<Time, Time>> lessonsSchedule_;
	unique_ptr<wifstream> file_;
	vector<wstring> schdVec_, 
		schdOnFstLessn_ = { L"Путь в колледж", L"У братков", L"Путь домой + обед", L"Полезное время" },
		schdOnOthLessns_ = { L"Полезное время", L"Обед", L"Путь в колледж", L"Путь домой + ужин" };
	vector<Note> edNotes_, notes_;

	void fillLessonsSchd();
	void fillSchdVec();
	void parseLessons();
	void createOthNotes();
	void createSchdFstLessn(const Note&);
	void createSchdOthLessns(const Note&);
};

wstring dateFromStr(const wstring&);
pair<int, int> timeFromStr(const string&);
wstring getTitle(const wstring&);
Time castTimeToZeroMins(const Time&);