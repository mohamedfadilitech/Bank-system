#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsLoginScreen.h"
#include "clsLoginHistoryScreen.h"
#include "Global.h"
#include <iomanip>

using namespace std;

class clsMainScreen : protected clsScreen {
private:
    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6, 
        eManageUsers = 7, eUsersLoginHistory = 8, eExit = 9
    };
    static short _readMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short choice = clsInputValidate::readIntBetween("",1, 9);
        return choice;
    }

    static void _goBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";
        system("pause>0");
        showMainMenu();
    }

    static void _showAllClientsScreen()
    {
		clsClientListScreen::showClientsList();
    }

    static void _showAddNewClientsScreen()
    {
		clsAddNewClientScreen::addNewClient();
    }

    static void _showDeleteClientScreen()
    {
		clsDeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen()
    {
		clsUpdateClientScreen::updateClient();
    }

    static void _showFindClientScreen()
    {
		clsFindClientScreen::showFindClientScreen();
    }

    static void _showTransactionsMenu()
    {
		clsTransactionsScreen::showTransactionsMenu();
    }

    static void _showManageUsersMenu()
    {
		clsManageUsersScreen::showManageUsersMenu();
    }

    static void _showLoginHistoryMenu() {
        clsLoginHistoryScreen::showLogList();
    }

    static void _logOut()
    {
		currentUser = clsUser::getEmptyUserObject(); // we will set the current user to empty user object to clear the current user data after logout, and then we will show the login screen again.
        clsLoginScreen::showLoginScreen();
    }


    static void _performMainMenuOption(enMainMenuOptions mainMenuOption)
    {
        switch (mainMenuOption)
        {
        case enMainMenuOptions::eListClients:
            system("cls");
            _showAllClientsScreen();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eAddNewClient:
            system("cls");
            _showAddNewClientsScreen();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eDeleteClient:
            system("cls");
            _showDeleteClientScreen();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eUpdateClient:
            system("cls");
            _showUpdateClientScreen();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eFindClient:
            system("cls");
            _showFindClientScreen();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eShowTransactionsMenu:
            system("cls");
            _showTransactionsMenu();
            _goBackToMainMenu();
            break;

        case enMainMenuOptions::eManageUsers:
            system("cls");
            _showManageUsersMenu(); 
             _goBackToMainMenu();
            break;
        case enMainMenuOptions :: eUsersLoginHistory:
            system("cls");
            _showLoginHistoryMenu();
            _goBackToMainMenu();

        case enMainMenuOptions::eExit:
            system("cls");
            _logOut();
            break;
        }
    }

public:

    static void showMainMenu()
    {
        system("cls");
        _drawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Users Login History.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performMainMenuOption((enMainMenuOptions)_readMainMenuOption());
    }
};