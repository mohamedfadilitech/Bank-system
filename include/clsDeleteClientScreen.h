#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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

public:
    static void showDeleteClientScreen()
    {
        if (!checkAccessRights(clsUser::enPermissions::pDeleteClient))
			return;
        _drawScreenHeader("\tDelete Client Screen");

        string accountNumber;
        char confirmation;

        accountNumber = clsInputValidate::readString("\nPlease Enter Account Number: ");
        while (!clsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("\nAccount number is not found, choose another one: ");
        }

		clsBankClient client = clsBankClient::find(accountNumber); // find the client using the account number and return it as a client object
        _print(client);

        do {
            confirmation = clsInputValidate::readChar("Are you sure you want to delete this account? (Y/N): ");
           } while (confirmation != 'y' && confirmation != 'n');
            
        if (confirmation == 'n')
            return;
        if (client.deleteClient()) {
            cout << "\nAccount Deleted Successfully :-)\n";
			_print(client);
           }
        else {
           cout << "Error client not deleted \n";
          }
    }
};

