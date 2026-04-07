#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsPerson.h"
#include "models/clsUser.h"
#include "core/clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
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
        cout << "\nUsername    : " << user.getUserName();
        cout << "\nPassword    : " << user.getPassword();
        cout << "\nPermissions : " << user.getPermissions();
        cout << "\n___________________\n";
    }

public:

    static void showFindUserScreen()
    {
        _drawScreenHeader("\t  Find User Screen");

        string userName;
        userName = clsInputValidate::readString("\nPlease Enter Username: ");
        while (!clsUser::isUserExist(userName))
        {
            userName = clsInputValidate::readString("\nUser is not found, choose another one: ");
        }

        clsUser user1 = clsUser::find(userName);

        if (!user1.isEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _printUser(user1);
    }

};