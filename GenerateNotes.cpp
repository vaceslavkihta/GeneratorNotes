#include "GenerateNotes.h"

using GN = GenerateNotes;

GN::GenerateNotes(const string& pathToGenDir, const string& pathToSchd):pars(pathToSchd), pathToDir(pathToGenDir) {
	pars.parsing();
	notes_ = pars.getEdNotes();
	vector<Note> t = pars.getNotes();
	notes_.insert(notes_.end(), t.begin(), t.end());
	cout << notes_.size();
}


void GN::generate() {
	setlocale(LC_ALL, "RU");
	int counter = 0;
	for (auto itEnd = notes_.end(), it = notes_.begin(); it != itEnd; ++it) {
		string newPath = pathToDir + "/" + std::format("{:%Y-%m-%d-%H%M%S}", chrono::system_clock::now()) + "_" + to_string(++counter) + ".md";

		wofstream file(newPath  );
		if (!file.is_open()) { cerr << "файл не открылся: " << newPath << endl; }

		file.imbue(std::locale(file.getloc(),
			new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, codecvt_mode(little_endian | generate_header)>));
		file << L"---\n" << (*it).getText() << endl
			<< L"tags: \n"
			<< L" - task" << L"\n---";
		/*std::this_thread::sleep_for(std::chrono::seconds(1));*/
	}
	cout << "Итого: " << counter << endl;
}