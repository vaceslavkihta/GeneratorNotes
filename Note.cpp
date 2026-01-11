#include "Note.h"

Note::Note(
    const string& title,
    const string& status,
    const string& priority,
    const string& schdDate,
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
    cout << "title: " << title << endl
        << "status: " << status << endl
        << "priority: " << priority << endl
        << "scheduled: " << scheduled.first << "T" << getTimeStr(scheduled.second) << endl
        << "timeEstimate: " << timeEstimate << " endTime ( " << getTimeStr(scheduled.second + timeEstimate) << " )\n\n";
}
