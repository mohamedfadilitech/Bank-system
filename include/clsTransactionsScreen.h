#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include <iomanip>

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4, eShowMainMenu = 5
    };

    static short _readTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short choice = clsInputValidate::readIntBetween("",1, 5);
        return choice;
    }

    static void _showDepositScreen()
    {
		clsDepositScreen::showDepositScreen();
    }

    static void _showWithdrawScreen()
    {
        clsWithdrawScreen::showWthdrawScreen();
    }

    static void _showTotalBalancesScreen()
    {
		clsTotalBalancesScreen::showTotalBalancesScreen();
    }
    static void _showTransfer()
    {
        clsTransferScreen::showTransferScreen();
    }

    static void _goBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        showTransactionsMenu();
    }

    static void _performTransactionsMenuOption(enTransactionsMenuOptions transactionsMenuOption)
    {
        switch (transactionsMenuOption)
        {
        case enTransactionsMenuOptions::eDeposit:
            system("cls");
            _showDepositScreen();
            _goBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eWithdraw:
            system("cls");
            _showWithdrawScreen();
            _goBackToTransactionsMenu();
            break;

        case enTransactionsMenuOptions::eShowTotalBalance:
            system("cls");
            _showTotalBalancesScreen();
            _goBackToTransactionsMenu();
            break;
        case enTransactionsMenuOptions::eTransfer:
            system("cls");
            _showTransfer();
            _goBackToTransactionsMenu();
        case enTransactionsMenuOptions::eShowMainMenu:
            // do nothing here the main screen will handle it :-)
            break;
        }
    }

public:

    static void showTransactionsMenu()
    {
        if (!currentUser.checkAccessRights(clsUser::pTranactions))
            return;
        system("cls");
        _drawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performTransactionsMenuOption((enTransactionsMenuOptions)_readTransactionsMenuOption());
    }

};