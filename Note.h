#pragma once
#include <string>
#include "Time.h"

using namespace std;

struct Note {
    string title, status, priority;
    bool isAllDay = false;
    pair<string, Time> scheduled;
    int timeEstimate;

    Note(
        const string& title       = "",
        const string& status      = "open",
        const string& priority    = "normal",
        const string& schdDate    = "",
        const Time& schdTime      = Time(0, 0),
        int timeEstimate          = 0);
    void print();
};