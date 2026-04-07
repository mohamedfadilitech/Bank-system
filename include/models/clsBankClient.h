#pragma once
#include "models/clsPerson.h"
#include "core/clsString.h"
#include "core/clsDate.h"
#include <fstream>
#include <iostream>      
#include <string>
#include <vector>


using namespace std;
class clsBankClient : public clsPerson
{
private:
	enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
	enMode _mode; // flag to determine if the client object is empty or not and to determine the mode of the client object (empty or update)

	string _accountNumber;
	string _pinCode;
	double _accountBalance;
	bool  _markedForDelete = false; // flag to determine if the client is marked for delete or not

	//abstraction    
	//helper function to convert line to client object
	static clsBankClient _convertLineToClientObject(string& line, string separator = "#//#") {
		vector<string> vClientData = clsString::split(line, separator); // split the line into a vector of strings using the separator
		return clsBankClient(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6])); // create a new clsBankClient object using the data from the vector and return it
	}

	static clsBankClient _getEmptyClient() {
		return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	//helper function to load clients data from file and return it as a vector of clients
	static vector<clsBankClient> _loadClientsDataFromFile() {
		vector<clsBankClient> _vClients;
		fstream myFile;
		myFile.open("data/Clients.txt", ios::in); // open the file for reading 
		if (!myFile.is_open()) { // check if the file is open
			cout << "Error opening file!" << endl;
		}
		else
		{
			string line;// read the file line by line
			while (getline(myFile, line))// for each line, convert it to a client object and add it to the vector of clients
			{
				clsBankClient client = _convertLineToClientObject(line);// convert the line to a client object
				_vClients.push_back(client);// add the client object to the vector of clients
			}
		}
		myFile.close();
		return _vClients;
	}
	//helper function to save clients data to file
	void	_saveClientsDataToFile(vector<clsBankClient>& vClients) {
		fstream myFile;
		myFile.open("data/Clients.txt", ios::out); // open the file for writing 
		if (!myFile.is_open()) { // check if the file is open
			cout << "Error opening file!" << endl;
		}
		else
		{
			for (clsBankClient& c : vClients)
			{
				if (c._markedForDelete == false) { // check if the client is not marked for delete before writing it to the file
					string line = c.getFirstName() + "#//#" + c.getLastName() + "#//#" + c.getEmail() + "#//#" + c.getPhone() + "#//#" +
						c.getAccountNumber() + "#//#" + c.getPinCode() + "#//#" + to_string(c.getAccountBalance()); // create a line to write to the file using the client data and the separator
					myFile << line << endl; // write the line to the file
				}
			}
			myFile.close(); // close the file
		}
	}
	//helper function to update the client data in the file using the current client object
	void _update() {

		vector<clsBankClient> _vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : _vClients)
		{
			if (c.getAccountNumber() == getAccountNumber())// find the client in the vector of clients using the account number and update the client data using the current client object
			{
				c = *this; // update the client data in the vector of clients using the current client object
				break;
			}
		}
		_saveClientsDataToFile(_vClients);
	}
	void _addNew() {
		vector<clsBankClient> _vClients = _loadClientsDataFromFile();
		_vClients.push_back(*this); // add the current client object to the vector of clients
		_saveClientsDataToFile(_vClients);
	}
	// helper For transfer logs

	static string _convertTransferDataToLine(clsUser &currentUser,clsBankClient &sender, clsBankClient& reciever,double amount ,string separator = "#//#") {
		string transferData = "";

		clsDate d;
		transferData += to_string(d.getDay()) + "/" +
			to_string(d.getMonth()) + "/" +
			to_string(d.getYear()) + "__" +
			to_string(d.getHours()) + ":" +
			to_string(d.getMinutes()) + ":" +
			to_string(d.getSeconds()) + separator;

		transferData += sender.getAccountNumber() + separator;
		transferData += reciever.getAccountNumber() + separator;
		transferData += to_string(amount) + separator;
		transferData += to_string(sender.getAccountBalance()) + separator;
		transferData += to_string(reciever.getAccountBalance()) + separator;
		transferData += currentUser.getUserName();
		return transferData;
	}


	//======================================================================================
public:
	//constructors

	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone,
		string accountNumber, string pinCode, double accountBalance) :
		clsPerson(firstName, lastName, email, phone),
		_accountNumber(accountNumber), _pinCode(pinCode), _accountBalance(accountBalance), _mode(mode) {
	}

	//transfer struct

	struct stTransfer {
		string date;
		string senderAccountNumber;
		string recieverAccountNumber;
		double amount;
		double recieverBalance;
		double senderBalance;
		string user;
	};



	//function to check if the client object is empty or not
	bool isEmpty() {
		return (_mode == enMode::emptyMode);
	}
	//setters
	void setMode(enMode mode) { _mode = mode; }
	void setPinCode(const string& pinCode) { _pinCode = pinCode; }
	void setAccountBalance(double accountBalance) { _accountBalance = accountBalance; }
	//read only property
	string getAccountNumber() const { return _accountNumber; }
	//getters
	string getPinCode() const { return _pinCode; }
	double getAccountBalance() const { return _accountBalance; }
	enMode getMode() const { return _mode; }

	//find function to find client by account number
	static clsBankClient find(const string& accountNumber) {
		fstream myFile;

		myFile.open("data/Clients.txt", ios::in); // open the file for reading 
		if (!myFile.is_open()) { // check if the file is open
			cout << "Error opening file!" << endl;
			return _getEmptyClient();
		}
		else
		{
			string line;// read the file line by line
			while (getline(myFile, line))// for each line, convert it to a client object and check if the account number matches
			{
				clsBankClient client = _convertLineToClientObject(line);// convert the line to a client object
				if (client.getAccountNumber() == accountNumber)
				{
					myFile.close();
					return client;
				}
			}
		}
		myFile.close();
		return _getEmptyClient();
	}

	//find function to find client by account number and pin code to be used in login function
	static clsBankClient find(const string& accountNumber, const string& pinCode) {
		fstream myFile;

		myFile.open("data/Clients.txt", ios::in); // open the file for reading 
		if (!myFile.is_open()) { // check if the file is open
			cout << "Error opening file!" << endl;
			return _getEmptyClient();
		}
		else
		{
			string line;// read the file line by line
			while (getline(myFile, line))// for each line, convert it to a client object and check if the account number matches
			{
				clsBankClient client = _convertLineToClientObject(line);// convert the line to a client object
				if (client.getAccountNumber() == accountNumber && client.getPinCode() == pinCode)
				{
					myFile.close();
					return client;
				}
			}
		}
		myFile.close();
		return _getEmptyClient();
	}
	//function to check if the client exists or not by account number
	static bool	isClientExist(const string& accountNumber) {
		clsBankClient client = find(accountNumber); //create a client object using the find function to find the client by account number and return true if the client object is not empty and return false if the client object is empty
		return (!client.isEmpty()); 
	}

	bool deleteClient() {
		vector<clsBankClient> _vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : _vClients) {
			if (c.getAccountNumber() == getAccountNumber()) {// find the client in the vector of clients using the account number and delete the client data using the current client object
				c._markedForDelete = true; // mark the client for delete using the current client object
				break;
			}
		}
		_saveClientsDataToFile(_vClients);
		*this = _getEmptyClient(); // set the current client object to empty client object to indicate that the client is deleted . the memory of the current client object will not be deleted but it will be set to empty client object to indicate that the client is deleted and to prevent any accidental use of the current client object after deleting it
		return true;
	}
	//function to create a new client object with the account number and the mode set to addNewMode and return it
	static clsBankClient getAddNewClientObject(const string& accountNumber) {
		return clsBankClient(addNewMode, "", "", "", "", accountNumber, "", 0); //calling the constructor to create a new client object with the account number and the mode set to addNewMode and return it
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExist = 2 };
	// flag to determine the result of the save function (failed because the client object is empty or succeeded)
	enSaveResults save() {

		switch (getMode()) {
		case enMode::emptyMode:
			return enSaveResults::svFaildEmptyObject;
		case enMode::updateMode:
			_update();
			return enSaveResults::svSucceeded;

		case enMode::addNewMode:
			if (isClientExist(getAccountNumber()))
				return enSaveResults::svFailedAccountNumberExist;
			else {
				_addNew();
				setMode(enMode::updateMode); // after adding the new client, set the mode to updateMode to allow updating the client data in the future
				return enSaveResults::svSucceeded;
			}
		default:
			return enSaveResults::svFaildEmptyObject;
		}
	}
	// This function is used to get the clients list from the file and return it as a vector of clients
	static vector<clsBankClient> getClientsList() {
		return _loadClientsDataFromFile();
	}
	// This function is used to get the total balances of all clients by iterating through the clients list and summing the account balances of all clients and return the total balances
	static double getTotalBalances() {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		double totalBalances = 0;
		for (clsBankClient& c : vClients) totalBalances += c.getAccountBalance();
		return totalBalances;
	}
	// This function is used to deposit an amount to the client's account by iterating through the clients list and finding the client with the same account number as the current client object and updating the account balance of the client in the vector of clients using the current client object and then saving the updated clients list to the file
	void deposit(double amount) {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients) {
			if (c.getAccountNumber() == getAccountNumber()) {
				c.setAccountBalance(c.getAccountBalance() + amount); // update the account balance of the client in the vector of clients using the current client object
				break;
			}
		}
		_saveClientsDataToFile(vClients);
		setAccountBalance(getAccountBalance() + amount); // update the account balance of the current client object to reflect the change in the account balance after depositing the amount
	}

	// This function is used to withdraw an amount from the client's account by iterating through the clients list and finding the client with the same account number as the current client object and updating the account balance of the client in the vector of clients using the current client object and then saving the updated clients list to the file

	void withdraw(double amount) {
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		for (clsBankClient& c : vClients) {
			if (c.getAccountNumber() == getAccountNumber()) {
				c.setAccountBalance(c.getAccountBalance() - amount); // update the account balance of the client in the vector of clients using the current client object
				break;
			}
		}
		_saveClientsDataToFile(vClients);
		setAccountBalance(getAccountBalance() - amount); // update the account balance of the current client object to reflect the change in the account balance after withdrawing the amount
	}


	//Helpers For Transfer Logs 
	static void loadTransferDataToFile(clsUser& currentUser, clsBankClient& sender, clsBankClient& reciever, double amount)
	{
		fstream myFile;
		myFile.open("data/TransferHistory.txt", ios::app);
		if (myFile.is_open())
		{
			myFile << _convertTransferDataToLine(currentUser, sender,reciever, amount)<< "\n";
			myFile.close();
		}
	}

	static  stTransfer convertTransferLinetoSt(string line, string seperator = "#//#") { 
		vector<string> vTransferData;
		stTransfer logs;

		vTransferData = clsString::split(line, seperator);

		logs.date = vTransferData[0];
		logs.senderAccountNumber = vTransferData[1];
		logs.recieverAccountNumber = vTransferData[2];
		logs.amount = stod(vTransferData[3]);
		logs.senderBalance = stod(vTransferData[4]);
		logs.recieverBalance = stod(vTransferData[5]);
		logs.user = vTransferData[6];

		return logs;
	}

	static vector<stTransfer> loadTransfersHistory() {
		vector<stTransfer> vTransfers;

		fstream myFile;
		myFile.open("data/TransferHistory.txt", ios::in);//read Mode

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				if (line.empty())
					break;
				stTransfer transfer = convertTransferLinetoSt(line);
				vTransfers.push_back(transfer);
			}
			myFile.close();
		}
		return vTransfers;
	}

	static vector<stTransfer> getTransfersList() {
		return loadTransfersHistory();
	}


};
