#include "Parser.h"

Parser::Parser(const string& path) :file_(make_unique<wifstream>(path)) {
	if (!file_) { throw std::runtime_error("file did not oppened"); }
	file_->imbue(locale(file_->getloc(),
		new codecvt_utf8<wchar_t, 0x10ffff, consume_header>));
	fillLessonsSchd();
	fillSchdVec();
}

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
		wstring line;
	setlocale(LC_ALL, "RU");
	while (getline(*file_, line)){
		if (!line.empty() && line != L"Расписание для группы 23ОИБ-2") {
			schdVec_.push_back(line);
			//cout << line << endl;
		}
	}
}

wstring dateFromStr(const wstring& str) {
	const wstring year = L"2026";
	wstring mounth = str.substr(str.find(L".")+1, 2), day = str.substr(0, 2);
	return year + L"-" + mounth + L"-" + day;
}

wstring getTitle(const wstring& str) {
	size_t fstSpacePos = str.find(L" ");
	size_t start = fstSpacePos + 1, end = str.find(L"|", start) - 1;
	int lenghtWord = end - start;
	return str.substr(start, lenghtWord);
}

void Parser::parseLessons() {
	Time edTimeStart, edTimeEnd;
	wstring date;
	Note lessonNote, edNote;
	edNote.title = L"Учёба";

	for (auto itStart = schdVec_.begin(), it = itStart, itEnd = schdVec_.end(); it != itEnd; ++it) {
		const wstring line = *it, prevLine = it == itStart ? L"" : * (it - 1);
		
		if (line.find(L".") == 2) {
			if (it != itStart){ 
				int lessonNum = prevLine[0] - '0';
				edTimeEnd = lessonsSchedule_.at(lessonNum + 1).second;
				edNote.timeEstimate = static_cast<int>(edTimeEnd - edTimeStart);

				edNotes_.push_back(edNote); 
				/*edNote.print();*/
			}			

			date = dateFromStr(line);
			const wstring& nextLine = *(it + 1);
			int lessonNum = nextLine[0] - '0';
			edTimeStart = lessonsSchedule_.at(lessonNum + 1).first;
			edNote.scheduled = { date, edTimeStart };
		}
		else {
			int lessonNum = line[0] - '0';
			Time startLessonTime = lessonsSchedule_.at(lessonNum + 1).first,
				endLessonTime = lessonsSchedule_.at(lessonNum + 1).second;
			lessonNote = Note(getTitle(line), L"open", L"normal", date, startLessonTime, static_cast<int>(endLessonTime - startLessonTime));
			/*lessonNote.print();*/
			notes_.push_back(lessonNote);
		}
	}
}

Time castTimeToZeroMins(const Time& time) {
	Time res = time;
	int hours = time.getHour(), mins = time.getMin();
	if (mins == 0) { ; }
	else { res.changeMin(0); }

	return res;
}

void Parser::createOthNotes() {
	for (int i = 0, size = edNotes_.size(); i < size; ++i) {
		Note currNote = edNotes_[i];
		if (currNote.scheduled.second != make_pair(8, 0)) { createSchdOthLessns(currNote); }
		else { createSchdFstLessn(currNote); }
	}
}

void Parser::createSchdFstLessn(const Note& currNote) {
	Time startTimeEd = currNote.scheduled.second, startTime = { 6, 0 }, endTime = startTime + 60;
	int timeEstimate;
	wstring date = currNote.scheduled.first;

	for (auto it = schdOnFstLessn_.begin(), itEnd = find(it, schdOnFstLessn_.end(), L"Путь домой + обед"); it != itEnd; ++it, startTime = endTime, endTime += 60) {
		timeEstimate = static_cast<int>(endTime - startTime);
		Note n(*it, L"open", L"normal", date, startTime, timeEstimate);
		/*n.print();*/
	}
	startTime = startTimeEd + currNote.timeEstimate;
	endTime = startTime + 90;

	for (auto it = find(schdOnFstLessn_.begin(), schdOnFstLessn_.end(), L"Путь домой + обед"), itEnd = schdOnFstLessn_.end(); it != itEnd; ++it, startTime = endTime, endTime = make_pair(19,00)) {
		Note n(*it, L"open", L"normal", date, startTime, static_cast<int>(endTime - startTime));
		/*n.print();*/
		notes_.push_back(n);
	}
}

void Parser::createSchdOthLessns(const Note& currNote) {
	Time startTimeEd = currNote.scheduled.second, startTime = { 6, 0 },
		endTime = startTimeEd > make_pair(11, 40) ? (startTimeEd - 45) - 60 : castTimeToZeroMins(startTimeEd) - 60;
	wstring date = currNote.scheduled.first;
	int timeEstimate = static_cast<int>(endTime - startTime);

	for (auto itEnd = find(schdOnOthLessns_.begin(), schdOnOthLessns_.end(), L"Путь в колледж") + 1, 
		it = schdOnOthLessns_.begin(); it != itEnd; ++it, startTime = endTime, endTime += 60) 
	{
		if (startTime > startTimeEd - 60) { endTime = startTimeEd; }
		timeEstimate = static_cast<int>(endTime - startTime);
		Note n(*it, L"open", L"normal", date, startTime, timeEstimate);
		/*n.print();*/
		notes_.push_back(n);
	}

	startTime = startTimeEd + currNote.timeEstimate;
	endTime = startTime + 90;
	Note n(schdOnOthLessns_[3], L"open", L"normal", date, startTime, static_cast<int>(endTime - startTime));
	/*n.print();*/
	notes_.push_back(n);

	if (startTimeEd < make_pair(11, 40)) {
		startTime = endTime;
		endTime = make_pair(19, 0);
		Note n(L"Полезное время", L"open", L"normal", date, startTime, static_cast<int>(endTime - startTime));
		/*n.print();*/
		notes_.push_back(n);
	}
}