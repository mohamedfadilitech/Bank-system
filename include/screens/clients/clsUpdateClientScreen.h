#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsPerson.h"
#include "models/clsBankClient.h"
#include "core/clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

private:
    static void _readClientInfo(clsBankClient& client)
    {
        string firstName = clsInputValidate::readString("Please enter the first name: ");
        string lastName = clsInputValidate::readString("Please enter the last name: ");
        string email = clsInputValidate::readString("Please enter the email: ");
        string phone = clsInputValidate::readString("Please enter the phone: ");
        string pinCode = clsInputValidate::readString("Please enter the pin code: ");
        double accountBalance = clsInputValidate::readDoubleNumber("Please enter the account balance: ");

        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setEmail(email);
        client.setPhone(phone);
        client.setPinCode(pinCode);
        client.setAccountBalance(accountBalance);
    }

    static void _print(clsBankClient& client)
    {
        cout << "\n\n Client Info: \n";
        cout << "==========================\n";
        cout << "\nAccount Number : " << client.getAccountNumber();
        cout << "\nClient Name    : " << client.getFirstName() + " " + client.getLastName();
        cout << "\nEmail          : " << client.getEmail();
        cout << "\nPhone          : " << client.getPhone();
        cout << "\nPin Code       : " << client.getPinCode();
        cout << "\nAccount Balance: " << client.getAccountBalance();
        cout << "\n==========================\n";
    }

public:
    static void updateClient()
    {
        if (!checkAccessRights(clsUser::enPermissions::pUpdateClients))
			return;
        string accountNumber;
        char confirmation;
        string title = "\t Update Client Screen";

        _drawScreenHeader(title);

        accountNumber = clsInputValidate::readString("Please enter the account number: ");
        while (!clsBankClient::isClientExist(accountNumber))
            accountNumber = clsInputValidate::readString("Account Number Not Found Please Enter A Valid One : ");

        clsBankClient client = clsBankClient::find(accountNumber);
        _print(client);

        do
        {
            confirmation = clsInputValidate::readChar("Are you sure you want to update this account? (Y/N): ");
        } while (confirmation != 'y' && confirmation != 'n');

        if (confirmation == 'n')
            return;

        cout << "\n\n Update Client Infos: ";
        cout << "\n=========================\n";
        _readClientInfo(client);

        clsBankClient::enSaveResults saveResult;
        saveResult = client.save();

        switch (saveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _print(client);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }

};