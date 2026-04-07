#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "core/clsInputValidate.h"
#include "screens/users/clsUsersListScreen.h"
#include "screens/users/clsAddNewUserScreen.h"    
#include "screens/users/clsDeleteUserScreen.h"
#include "screens/users/clsUpdateUserScreen.h"
#include "screens/users/clsFindUserScreen.h"
#include <iomanip>

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static short _readManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]: ";
		short choice = clsInputValidate::readIntBetween("", 1, 6);
        return choice;
    }

    static void _goBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        showManageUsersMenu();
    }

    static void _showListUsersScreen()
    {
        clsListUsersScreen::showUsersList();
    }

    static void _showAddNewUserScreen()
    {
		clsAddNewUserScreen::showAddNewUserScreen();
    }

    static void _showDeleteUserScreen()
    {
        clsDeleteUserScreen::showDeleteUserScreen();
    }

    static void _showUpdateUserScreen()
    {
		clsUpdateUserScreen::showUpdateUserScreen();
    }

    static void _showFindUserScreen()
    {
		clsFindUserScreen::showFindUserScreen();
    }
    static void _performManageUsersMenuOption(enManageUsersMenuOptions manageUsersMenuOption)
    {
        switch (manageUsersMenuOption)
        {
        case enManageUsersMenuOptions::eListUsers:
        {
            system("cls");
            _showListUsersScreen();
            _goBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eAddNewUser:
        {
            system("cls");
            _showAddNewUserScreen();
            _goBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eDeleteUser:
        {
            system("cls");
            _showDeleteUserScreen();
            _goBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eUpdateUser:
        {
            system("cls");
            _showUpdateUserScreen();
            _goBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eFindUser:
        {
            system("cls");
            _showFindUserScreen();
            _goBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eMainMenu:
        {
            // Do nothing here, the main screen will handle it.
        }
        }
    }

public:

    static void showManageUsersMenu()
    {
        if (!currentUser.checkAccessRights(clsUser::pManageUsers))
            return;
        system("cls");
        _drawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performManageUsersMenuOption((enManageUsersMenuOptions)_readManageUsersMenuOption());
    }

};