#pragma once
#include<cstdlib>
#include "core/clsDate.h"
using namespace std;

class clsUtil{
private:
	static const int _REPS = 4;
public:
	// This enum is used to specify the type of character we want to generate
	enum randomStuff
	{
		smallLetter,
		capitalLetter,
		specialChar,
		randomNumber,
		mixCharacters
	};
	// This function is used to generate a random number between 0 and 1
	static void Srand()
	{
		srand((unsigned)time(0));
	}
	// This function is used to generate a random number between min and max
	static int	ft_randomNumber(int min, int max) {
		int rand_num = rand() % (max - min + 1) + min;
		return rand_num;
	}
    // This function is used to generate a random character based on the type of character we want
	static char getRandomCharacter(randomStuff charType) {
		switch (charType) {
		case randomStuff::smallLetter:
			return (char)ft_randomNumber(97, 122);
		case randomStuff::capitalLetter:
			return (char)ft_randomNumber(65, 90);
		case randomStuff::specialChar:
			return (char)ft_randomNumber(33, 47);
		case randomStuff::mixCharacters:
			return (char)ft_randomNumber(33, 122);
		case randomStuff::randomNumber:
			return char('0' + ft_randomNumber(0, 9));
		default:
			return '\0';
		}
	}
	// This function is used to generate a random string of a given length and character type
	static string getRandomString(size_t length, randomStuff charType) {
		string randomString;
		for(int i = 0; i < length; i++) {
			randomString += getRandomCharacter(charType);
		}
		return randomString;
	}
	// This function is used to generate a random key in the format of "XXXX-XXXX
	static string	generateKey(randomStuff charType) {
		string word ;
		for (int i = 0; i < _REPS; i++) {
				word += getRandomString(_REPS, charType);
			if (i!= 3)
			word += "-";
		}
		return word;
	}
	// This function is used to generate multiple random keys based on the number of keys and character type specified
	static vector<string> generateKeys(size_t count, randomStuff type) {
		vector<string> keys;

		for (size_t i = 0; i < count; i++) keys.push_back(generateKey(type));
		
		return keys;
	}
	// This function is used to swap two integers without using a temporary variable
	static void swap(int& a, int& b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	// This function is used to swap two doubles without using a temporary variable and function overloading
	static void swap(double& a, double& b) {
		double tmp = a;
		a = b;
		b = tmp;
	}
	// This function is used to swap two strings using a temporary variable and function overloading
	static void swap(string& a, string& b) {
		string temp = a;
		a = b;
		b = temp;
	}
	// This function is used to swap two clsDate objects using a temporary variable and function overloading
	static void swap(clsDate& d1, clsDate& d2) {
		clsDate temp = d1;
		d1 = d2;
		d2 = temp;
	}
	// This function is used to shuffle an array of integers using the Fisher-Yates algorithm
	static void shuffleArray(int arr[], size_t size) {
		for (size_t i = 0; i < size; i++) {
			int randomIndex = ft_randomNumber(0, (int)(size - 1));
			swap(arr[i], arr[randomIndex]);
		}
	}
	// This function is used to shuffle an array of strings using the Fisher-Yates algorithm and function overloading
	static void shuffleArray(string arr[], size_t size) {
		for (size_t i = 0; i < size; i++) {
			int randomIndex = ft_randomNumber(0, (int)(size - 1));
			swap((arr[i]), (arr[randomIndex]));
		}
	}
	// This function is used to fill an array of integers with random numbers between 0 and 100
	static void fillArrayWithRandom(int arr[], size_t size,int min, int max) {
		for (size_t i = 0; i < size; i++) arr[i] = ft_randomNumber(min, max);
	}
	// This function is used to fill an array of strings with random strings of a given length and character type
	static void fillArrayWithRandom(string arr[], size_t size, randomStuff charType, int wordLength) {
		for (size_t i = 0; i < size; i++) arr[i] = getRandomString(wordLength, charType);
	}
	// This function is used to print a specified number of tabs
	static void Tabs(size_t numberOfTabs) {
		while (numberOfTabs < 0) {
			cout << "Number of tabs must be greater than 0. Please enter a valid number: ";
			cin >> numberOfTabs;
		}
		for (size_t i = 0; i < numberOfTabs; i++) cout << "\t";
	}

	// This function is used to decrypt a string that was encrypted using the Caesar cipher method with a given encryption key
	static void encryptText(string& str, size_t encryptionKey) {
		while (encryptionKey == 0) {
			cout << "Encryption key must be greater than 0: ";
			cin >> encryptionKey;
		}

		for (char& c : str) {
			if (islower(c))
				c = 'a' + (c - 'a' + encryptionKey) % 26;
			else if (isupper(c))
				c = 'A' + (c - 'A' + encryptionKey) % 26; 
			else if (isdigit(c))
				c = '0' + (c - '0' + encryptionKey) % 10;
		}
	}
	//example
	//'x' - 'a' = 23
	//	23 + 3 = 26
	//	26 % 26 = 0
	//	'a' + 0 = 'a'

	// This function is used to decrypt a string that was encrypted using the Caesar cipher method with a given encryption key
	static void decryptText(string& str, size_t encryptionKey) {
		while (encryptionKey == 0) {
			cout << "Encryption key must be greater than 0: ";
			cin >> encryptionKey;
		}
		for (char& c : str) {
			if (islower(c))
				c = 'a' + (c - 'a' - encryptionKey + 26) % 26; 
			else if (isupper(c))
				c = 'A' + (c - 'A' - encryptionKey + 26) % 26;  
			else if (isdigit(c))
				c = '0' + (c - '0' + encryptionKey + 10) % 10;
		}
	}
	// This function is used to convert a number to its English words representation
	static string	digitsToString(double number) {

		if (number == 0)
			return "";
		if (number >= 1 && number <= 19) {
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return arr[(int)number] + " ";
		}
		if (number >= 20 && number <= 99) {
			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			return arr[(int)number / 10] + " " + digitsToString((int)number % 10);
		}
		if (number >= 100 && number <= 999) {
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
			return arr[(int)number / 100] + " Hundred " + digitsToString((int)number % 100);
		}
		if (number >= 1000 && number <= 999999) {
			return digitsToString(number / 1000) + "Thousand " + digitsToString((int)number % 1000);
		}

		if (number >= 1000000 && number <= 999999999) {
			return digitsToString(number / 1000000) + "Million " + digitsToString((int)number % 1000000);
		}
		if (number >= 1000000000 && number <= 999999999999) {
			return digitsToString(number / 1000000000) + "Billion " + digitsToString((int)number % 1000000000);
		}

		return "Out Of range";
	}
	
};
