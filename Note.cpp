#include "Note.h"

Note::Note(
    const wstring& title,
    const wstring& status,
    const wstring& priority,
    const wstring& schdDate,
    const Time& schdTime,
    int timeEstimate
) :
    title(title),
    status(status),
    priority(priority),
    scheduled({ schdDate, schdTime }),
    timeEstimate(timeEstimate)
{
    ;
}

void Note::print() {
    wcout << L"title: " << title << endl
        << L"status: " << status << endl
        << L"priority: " << priority << endl
        << L"scheduled: " << scheduled.first << L"T" << scheduled.second << endl
        << L"timeEstimate: " << timeEstimate << L" endTime ( " << (scheduled.second + timeEstimate) << L" )\n\n";
}

wstring Note::getText() {
    wstring res = L"title: " + title +
        L"\nstatus: " + status +
        L"\npriority: " + priority +
        L"\nscheduled: " + scheduled.first + L"T" + getTimeStr(scheduled.second) +
        L"\ntimeEstimate: " + to_wstring(timeEstimate);
    return res;
}