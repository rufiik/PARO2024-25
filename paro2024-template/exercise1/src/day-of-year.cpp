#include "day-of-year.hpp"
#include <array>

int dayOfYear(int month, int dayOfMonth, int year) {
#define FEBRUARY 1
    std::array<int, 12> daysOfMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12)
        throw "lol xd";
    if (dayOfMonth < 1)
        throw "second strike";
    // TODO: check if day is greater that days in current moth?? maybe..

    int currMonthIndex = 0;
    int numOfDays = 0;
    while (currMonthIndex < month-1)
    {
        numOfDays += daysOfMonths.at(currMonthIndex);
        if (currMonthIndex == FEBRUARY && isLeap(year))
            numOfDays++;
        currMonthIndex++;
    }
    numOfDays += dayOfMonth;

    return numOfDays;
}

bool isLeap(int year) {
    return year%4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
