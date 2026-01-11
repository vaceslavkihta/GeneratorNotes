#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include "Time.h"
#include "Parser.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    const string path = "C:/Users/slava/OneDrive/Documents/ForObsidian/sourse.txt";
    Parser a(path);
    vector<Note> vec = a.parseLessons();
    
}