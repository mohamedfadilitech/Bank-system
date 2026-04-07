#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsPerson.h"
#include "models/clsUser.h"
#include "core/clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{
private:

    static void _readUserInfo(clsUser& user)
    {
        user.setFirstName(clsInputValidate::readString("\nEnter FirstName: "));
        user.setLastName(clsInputValidate::readString("\nEnter LastName: "));
        user.setEmail(clsInputValidate::readString("\nEnter Email: "));
        user.setPhone(clsInputValidate::readString("\nEnter Phone: "));
        user.setPassword(clsInputValidate::readString("\nEnter Password: "));
        cout << "\nEnter Permission: ";
        user.setPermissions(_readPermissionsToSet());
    }

    static void _printUser(clsUser &user)
    {
        //string encryptedPasswd = user.getPassword();
        //clsUtil::encryptText(encryptedPasswd, 5);
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

    static int _readPermissionsToSet()
    {
        int permissions = 0;
        char answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Log History? y/n? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permissions += clsUser::enPermissions::PLogHistory;
        }

        return permissions;
    }

public:

    static void showUpdateUserScreen()
    {
        _drawScreenHeader("\tUpdate User Screen");

        string userName = "";

        userName = clsInputValidate::readString("\nPlease Enter User Username: ");

        while (!clsUser::isUserExist(userName))
        {
            userName = clsInputValidate::readString("\nUser is not found, choose another one: ");
        }

        clsUser user1 = clsUser::find(userName);

        _printUser(user1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _readUserInfo(user1);

            clsUser::enSaveResults saveResult;

            saveResult = user1.save();

            switch (saveResult)
            {
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _printUser(user1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;
            }
            }
        }
    }
};