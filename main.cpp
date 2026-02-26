#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <chrono>
#include "Time.h"
#include "Parser.h"
#include "GenerateNotes.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    const string path = "C:/Users/slava/OneDrive/Documents/ForObsidian/sourse.txt",
        pathT = "C:/Users/slava/OneDrive/Documents/1488/TaskNotes/Tasks";

   
    GenerateNotes GN(pathT, path);
    GN.generate();

    
    
}