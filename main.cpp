#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include "Time.h"

using namespace std;


int main(){

    const string path = "C:/Users/slava/OneDrive/Рабочий стол/1/sourse.txt";
    setlocale(LC_ALL, "RU");
    ifstream f(path);
    string line;
    while (getline(f, line)) {
        if (line != "") { cout << line << endl; }
    }
}