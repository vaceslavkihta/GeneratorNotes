#include "Parser.h"

void Parser::fillLessonsSchd() {
	Time startTime(8, 0), endTime = startTime;
	for (int i = 1, durationLesson = 95, durationRecess = 10; i < 7; ++i, endTime += durationRecess, startTime = endTime) {
		if (i == 2) { durationRecess = 20; }
		else { durationRecess = 10; }
		endTime += durationLesson;
		lessonsSchedule_.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(i + 1),
			std::forward_as_tuple(startTime, endTime)
		);
	}
}

void Parser::fillSchdVec() {
	string line;
	while (getline(*file_, line)){
		if (line != "" && line != "Расписание для группы 23ОИБ-2") {
			schdVec_.push_back(line);
			//cout << line << endl;
		}
	}
}

string dateFromStr(const string& str) {
	const string year = "2026";
	string mounth = str.substr(str.find(".")+1, 2), day = str.substr(0, 2);
	return year + "." + mounth + "." + day;
}

string getTitle(const string& str) {
	size_t fstSpacePos = str.find(" ");
	size_t start = fstSpacePos + 1, end = str.find("|", start) - 1;
	int lenghtWord = end - start;
	return str.substr(start, lenghtWord);
}

vector<Note> Parser::parseLessons() {
	Time edTimeStart, edTimeEnd;
	string date;
	Note lessonNote, edNote;
	edNote.title = "Учёба";

	for (auto itStart = schdVec_.begin(), it = itStart, itEnd = schdVec_.end(); it != itEnd; ++it) {
		const string& line = *it, & prevLine = it == itStart ? "" : * (it - 1);
		
		if (line.find(".") == 2) {
			if (it != itStart){ 
				int lessonNum = prevLine[0] - '0';
				edTimeEnd = lessonsSchedule_.at(lessonNum + 1).second;
				edNote.timeEstimate = static_cast<int>(edTimeEnd - edTimeStart);

				edNotes_.push_back(edNote); 
				edNote.print();
			}			

			date = dateFromStr(line);
			const string& nextLine = *(it + 1);
			int lessonNum = nextLine[0] - '0';
			edTimeStart = lessonsSchedule_.at(lessonNum + 1).first;
			edNote.scheduled = { date, edTimeStart };
		}
		else {
			int lessonNum = line[0] - '0';
			Time startLessonTime = lessonsSchedule_.at(lessonNum + 1).first,
				endLessonTime = lessonsSchedule_.at(lessonNum + 1).second;
			lessonNote = Note(getTitle(line), "open", "normal", date, startLessonTime, endLessonTime - startLessonTime);
			lessonNote.print();
		}
	}
	return notes_;
}

//Time castTimeToZeroMins(const Time& time) {
//	Time res = time;
//	int hours = time.getHour(), mins = time.getMin();
//	if (mins == 0) { ; }
//	else { res.changeMin(0); }
//
//	return res;
//}
//
//void Parser::createOthNotes() {
//	for (int i = 0, size = edNotes_.size(); i < size; ++i) {
//		Note currNote = edNotes_[i];	
//		
//		if (currNote.startDateTime.second == make_pair(8, 0)) { ; }
//		else { createSchdOthLessns(currNote); }
//	}
//}
//
//void Parser::createSchdOthLessns(const Note& currNote) {
//	Time startTimeEd = currNote.startDateTime.second, endTime = startTimeEd, startTime = castTimeToZeroMins(endTime);
//	string date = currNote.startDateTime.first;
//
//	for (auto itEnd = schdOnOthLessns_.end(),
//		it = find(schdOnOthLessns_.begin(), itEnd, "Путь в колледж"); it != itEnd; --it) {
//		notes_.push_back(Note(*it, false, date, startTime, date, endTime));
//
//
//		/*
//			if edTimeNote.time > 11.40:
//				where note.title == "Путь в колледж" do startTime = edTimeNote.time - 45
//			else:
//				where note.title == "Путь в колледж" do startTime = castTimeToZeroMins(edTimeNote.time)
//
//		*/
//	}
//}