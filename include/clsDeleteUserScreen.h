#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:
    static void _printUser(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.getFirstName();
        cout << "\nLastName    : " << user.getLastName();
		cout << "\nFull Name   : " << user.getFirstName() + " " + user.getLastName();
        cout << "\nEmail       : " << user.getEmail();
        cout << "\nPhone       : " << user.getPhone();
        cout << "\nUser Name   : " << user.getUserName();
        cout << "\nPassword    : " << user.getPassword();
        cout << "\nPermissions : " << user.getPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showDeleteUserScreen()
    {
        _drawScreenHeader("\tDelete User Screen");

        string userName = "";
		char confirmation;

        userName = clsInputValidate::readString("\nPlease Enter Username: ");
        while (!clsUser::isUserExist(userName))
        {
            userName = clsInputValidate::readString("\nUser is not found, choose another one: ");
        }

        clsUser user = clsUser::find(userName);
        _printUser(user);

        do {
            confirmation = clsInputValidate::readChar("Are you sure you want to delete this account? (Y/N): ");
        } while (confirmation != 'y' && confirmation != 'n');

        if (confirmation == 'n')
            return;
        if (user.deleteUser()) {
            cout << "\nAccount Deleted Successfully :-)\n";
            _printUser(user);
        }
        else {
            cout << "Error User not deleted \n";
        }
    }

};
