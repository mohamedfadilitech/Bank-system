#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsBankClient.h"
#include "core/clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{
private:

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


    static string _readAccountNumber()
    {
        string accountNumber = "";

        cout << "\nPlease enter account number: ";
        cin >> accountNumber;

        return accountNumber;
    }

public:

    static void showDepositScreen()
    {
        char confirmation;
        _drawScreenHeader("\t   Deposit Screen");

        string accountNumber = _readAccountNumber();

        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nClient with [" << accountNumber << "] does not exist.\n";
            accountNumber = _readAccountNumber();
        }

		clsBankClient client = clsBankClient::find(accountNumber); // find the client using the account number and return it as a client object
        _print(client);

        double amount = 0;
		amount = clsInputValidate::readDoubleNumberBetween("\nPlease enter deposit amount: ", 0.01, 100000000);

        do {
            confirmation = clsInputValidate::readChar("Do Wanna Really Preform This Operation. Y | N : ");
        } while (confirmation != 'y' && confirmation != 'n');

        if (confirmation == 'y')
        {
            client.deposit(amount);

			cout << "\nOperation was done successfully.\n";
            cout << "\nNew balance is: " << client.getAccountBalance();
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};