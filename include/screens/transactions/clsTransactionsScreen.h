#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "core/clsInputValidate.h"
#include "screens/transactions/clsDepositScreen.h"
#include "screens/transactions/clsWithdrawScreen.h"
#include "screens/transactions/clsTotalBalancesScreen.h"
#include "screens/transactions/clsTransferScreen.h"
#include "screens/transactions/clsTransferLogsScreen.h"
#include <iomanip>

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenu = 6
    };

    static short _readTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short choice = clsInputValidate::readIntBetween("",1, 6);
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
    static void _showTransferLog()
    {
        clsTransferLogsScreen::showTransfersList();
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
            break;
        case enTransactionsMenuOptions::eTransferLog:
            _showTransferLog();
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
        cout << setw(37) << left << "" << "\t[5] Transfer Logs.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performTransactionsMenuOption((enTransactionsMenuOptions)_readTransactionsMenuOption());
    }

};