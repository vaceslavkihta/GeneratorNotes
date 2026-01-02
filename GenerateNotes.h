#include <vector>
#include "Reader.h"

#pragma once

class GenerateNotes {
public:
	GenerateNotes(); // call Reader::read


private:
	Reader rObj;
};

// Сколько сегодня заметок надо создать
// Прочитать расписание на Понедельник и сделать выводы о расписании


/* Если к первой паре, то
* Завтрак с 05:00 до 06:00
* Путь до колледжа до 07:00
* Учёба с 08:00 до n;
* Путь до дома n+90
* Полезное время с n+90 до 19:00
*/

// Reader (читает и предоставляет это в каком то формате) 
// GenerateNotes (принимает значение reader и генерирует заметки)

/*---
title: Учёба
allDay : false
startTime : 11 : 40
endTime : 16 : 45
date : 2025 - 10 - 20 // Обратить внимание на формат даты
completed : null
---*/