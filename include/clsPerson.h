#pragma once
#include <iostream>
#include <string>

using namespace std;

class clsPerson {
private:
	string _firstName;
	string _lastName;
	string _email;
	string _phone;
public:
	//constructor
	clsPerson(string firstName, string lastName, string email, string phone):
		_firstName(firstName), _lastName(lastName), _email(email), _phone(phone) {
	}
	//setters
	void setFirstName(const string& firstName) { _firstName = firstName; }
	void setLastName(const string& lastName) { _lastName = lastName; }
	void setEmail(const string& email) { _email = email; }
	void setPhone(const string& phone) { _phone = phone; }

	//getters
	string getFirstName() const { return _firstName; }
	string getLastName() const { return _lastName; }
	string getEmail() const { return _email; }
	string getPhone() const { return _phone; }

};