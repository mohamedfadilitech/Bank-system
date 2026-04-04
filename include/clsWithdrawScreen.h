#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

        do
        {
            cout << "\nPlease enter account number: ";
            cin >> accountNumber;

            if (accountNumber.empty())
                cout << "\nAccount number cannot be empty, try again.";

        } while (accountNumber.empty());

        return accountNumber;
    }

public:

    static void showWthdrawScreen()
    {
        char confirmation;
        _drawScreenHeader("\t   Withdraw Screen");

        string accountNumber = _readAccountNumber();

        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nClient with [" << accountNumber << "] does not exist.\n";
            accountNumber = _readAccountNumber();
        }

        clsBankClient client = clsBankClient::find(accountNumber); // find the client using the account number and return it as a client object
        _print(client);

        double amount = 0;
        amount = clsInputValidate::readDoubleNumberBetween("\nPlease enter withdraw amount: ", 0.01, client.getAccountBalance());

        do {
            confirmation = clsInputValidate::readChar("Do Wanna Really Preform This Operation. Y | N : ");
        } while (confirmation != 'y' && confirmation != 'n');

        if (confirmation == 'y')
        {
            client.withdraw(amount);

			cout << "\nOperation was done successfully.\n";
            cout << "\nNew balance is: " << client.getAccountBalance();
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }
};