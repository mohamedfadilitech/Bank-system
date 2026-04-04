#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDeleteClientScreen.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:
    // This function is used to read the client info from the user and set it to the client object
    static void _readClientInfo(clsBankClient& client) {
        // read the client info from the user
        string firstName = clsInputValidate::readString("Please enter the first name: ");
        string lastName = clsInputValidate::readString("Please enter the last name: ");
        string email = clsInputValidate::readString("Please enter the email: ");
        string phone = clsInputValidate::readString("Please enter the phone: ");
        string pinCode = clsInputValidate::readString("Please enter the pin code: ");
        double accountBalance = clsInputValidate::readDoubleNumber("Please enter the account balance: ");
        // set the client info using the setters
        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setEmail(email);
        client.setPhone(phone);
        client.setPinCode(pinCode);
        client.setAccountBalance(accountBalance);
    }

    static void _print(clsBankClient& client) {

		cout << "\n\n Client Info: \n";
		cout << "==========================\n";
        cout << "\nAccount Number: " << client.getAccountNumber();
        cout << "\nClient Name: " << client.getFirstName() + " " + client.getLastName();
        cout << "\nEmail: " << client.getEmail();
        cout << "\nPhone: " << client.getPhone();
        cout << "\nPin Code: " << client.getPinCode();
		cout << "\nAccount Balance: " << client.getAccountBalance();
        cout << "\n==========================\n";
    }
public:

    static void addNewClient()
    {
        if (!checkAccessRights(clsUser::enPermissions::pAddNewClient))
            return;
        string accountNumber;

        string title = "\t Add New Client Screen" ;
		_drawScreenHeader(title);

        accountNumber = clsInputValidate::readString("Please Enter The Account Number : ");
        while (clsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account Number Not Found Please Enter A Valid One : ");
        }

		clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber); // create new empty object with the account number and the mode set to addNewMode
        _readClientInfo(newClient);

        clsBankClient::enSaveResults saveResult;
        saveResult = newClient.save();

        switch (saveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Added Successfully :-)\n";
			_print(newClient);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::enSaveResults::svFailedAccountNumberExist:
            cout << "\nError account was not saved because the account number already exists";
            break;
        }
    }

};