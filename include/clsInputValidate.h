#pragma once
#include "clsDate.h"
#include"clsUtil.h"


using namespace std;

class clsInputValidate {
private:
	static int dateToNumber(const clsDate& d) {
		return d.getYear() * 10000 +
			d.getMonth() * 100 +
			d.getDay();
		// 15/06/2021 → 20210615
	}
public:
	static bool isNumberBetween(int num, int lower, int higher)	{
		return num >= lower && num <= higher;
	}
	static bool isNumberBetween(double num, double lower, double higher) {
		return num >= lower && num <= higher;
	}
	//This function is used to see if the date is between the lower and higher date
	static bool isDateBetween(const clsDate& date, const clsDate& lower, const clsDate& higher) {
		int dateNum = dateToNumber(date);
		int lowerNum = dateToNumber(lower);
		int higherNum = dateToNumber(higher);
		if (lowerNum > higherNum)
			clsUtil::swap(lowerNum, higherNum);
		return dateNum >= lowerNum && dateNum <= higherNum;
	}
	// This function is used to read an integer from the user and validate it
    static int readInt(const string str) {
        int num;

        do {
            cout << str;
            cin >> num;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (cin.peek() != '\n') {
                cin.ignore(1000, '\n');
            }
            else {
                cin.ignore(1000, '\n');
                break;
            }

        } while (true);
        return num;
    }
	// This function is used to read an integer from the user and validate that it is between the lower and higher values
	static int readIntBetween(const string str, int lower, int higher) {
		int num;
		do {
			num = readInt(str);
			if (!isNumberBetween(num, lower, higher)) {
				cout << "Number must be between " << lower << " and " << higher << ". Please enter a valid number." << endl;
			}
		} while (!isNumberBetween(num, lower, higher));
		return num;
	}
	// This function is used to read a double from the user and validate it

	static double readDoubleNumber(const string str) {
		
		double num;

		do {
			cout << str;
			cin >> num;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (cin.peek() != '\n') {
				cin.ignore(1000, '\n');
			}
			else {
				cin.ignore(1000, '\n');
				break;
			}
		} while (true);
		return num;
	}
	// This function is used to read a double from the user and validate that it is between the lower and higher values
	static double readDoubleNumberBetween(const string str, double lower, double higher) {
		double num;
		do {
			num = readDoubleNumber(str);
			if (!isNumberBetween(num, lower, higher)) {
				cout << "Number must be between " << lower << " and " << higher << ". Please enter a valid number." << endl;
			}
		} while (!isNumberBetween(num, lower, higher));
		return num;
	}
	// This function is used to read a string from the user
	static string readString(const string str) {
		string s;
		cout << str;
		getline(cin >> ws, s);
		return s;
	}
	// this function is used to read a date from the user and validate it
	static bool isValidDate(const clsDate& date) {
		return !(date.getYear() <= 0 || date.getMonth() <= 0 || date.getMonth() > 12 || date.getDay() <= 0 || date.getDay() > clsDate::daysInMonth(date));
	}
	
	// read character from the user and validate that it is either 'y' or 'n'
	static char readChar(const string &str)
	{
		char c;
		cout << str;
		cin >> c;
		if (cin.fail()) {
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n');
		}
		else if (cin.peek() != '\n') {// check if there are extra characters after the character input
			cin.ignore(1000, '\n');
		}
		else {
			cin.ignore(1000, '\n'); // ignore the newline character after reading the character
			c = tolower(c);
			return c;
		}
		return '\0';
	}
};

