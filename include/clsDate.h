#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class clsDate
{
private:
    int _day;
    int _month;
    int _year;
    int _hours;
    int _minutes;
    int _seconds;

    static vector<string> _split(string date, const string& delim)
    {
        string word;
        size_t pos = 0;
        vector<string> vStr;

        while ((pos = date.find(delim)) != string::npos)
        {
            word = date.substr(0, pos);
            if (word != "") vStr.push_back(word);
            date.erase(0, pos + delim.length());
        }

        if (date != "") vStr.push_back(date);
        return vStr;
    }

public:

    // Constructor 1 — current date and time
    clsDate()
    {
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);

        _day = localTime.tm_mday;
        _month = localTime.tm_mon + 1;
        _year = localTime.tm_year + 1900;
        _hours = localTime.tm_hour;
        _minutes = localTime.tm_min;
        _seconds = localTime.tm_sec;
    }

    // Constructor 2 — from string "dd/mm/yyyy"
    clsDate(string date)
    {
        vector<string> vDate = _split(date, "/");
        _day = stoi(vDate.at(0));
        _month = stoi(vDate.at(1));
        _year = stoi(vDate.at(2));
        _hours = _minutes = _seconds = 0;
    }

    // Constructor 3 — from day, month, year
    clsDate(int day, int month, int year)
        : _day(day), _month(month), _year(year),
        _hours(0), _minutes(0), _seconds(0)
    {
    }

    // Getters & Setters
   // Getters & Setters
    int  getDay()     const { return _day; }
    void setDay(int day) { _day = day; }

    int  getMonth()   const { return _month; }
    void setMonth(int month) { _month = month; }

    int  getYear()    const { return _year; }
    void setYear(int year) { _year = year; }

    int  getHours()   const { return _hours; }
    void setHours(int hours) { _hours = hours; }

    int  getMinutes() const { return _minutes; }
    void setMinutes(int minutes) { _minutes = minutes; }

    int  getSeconds() const { return _seconds; }
    void setSeconds(int seconds) { _seconds = seconds; }

    // Print date
    void print()
    {
        cout << _day << "/" << _month << "/" << _year << endl;
    }

    // Check if leap year
    static bool isLeapYear(int year)
    {
        return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
    }

    // Get number of days in a month
    static int daysInMonth(clsDate date)
    {
        static const int numberOfDays[12] =
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        return (date.getMonth() == 2)
            ? (isLeapYear(date.getYear()) ? 29 : 28)
            : numberOfDays[date.getMonth() - 1]; // ← كان getDay() خطأ
    }

};