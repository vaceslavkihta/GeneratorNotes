#pragma once
#include <string>
#include "Time.h"

using namespace std;

struct Note {
    wstring title, status, priority;
    bool isAllDay = false;
    pair<wstring, Time> scheduled;
    int timeEstimate;

    Note(
        const wstring& title      = L"",
        const wstring& status     = L"open",
        const wstring& priority   = L"normal",
        const wstring& schdDate   = L"",
        const Time& schdTime      = Time(0, 0),
        int timeEstimate          = 0);
    void print();
    wstring getText();
};