#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTransferLogsScreen : protected clsScreen {

    static void _printTransfersHistory(clsBankClient::stTransfer transfer)
    {
        cout << setw(8) << left << "" << "| ";
        cout << setw(22) << left << transfer.date << "| ";
        cout << setw(25) << left << transfer.senderAccountNumber << "| ";
        cout << setw(15) << left << transfer.recieverAccountNumber << "| ";
        printf("%-12.2f| ", transfer.amount);
        printf("%-12.2f| ", transfer.senderBalance);
        printf("%-12.2f| ", transfer.recieverBalance);
        cout << setw(12) << left << transfer.user;
    }

public:

    static void showTransfersList()
    {
        vector<clsBankClient::stTransfer> vTransfers = clsBankClient::getTransfersList();
        string title = "\t  Transfers History List";
        string subTitle = "\t    (" + to_string(vTransfers.size()) + ") Transfers(s).";

        system("cls");
        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << ""
            << "\n\t________________________________________________________________"
            << "____________________________________________________________________\n\n";

        cout << setw(8) << left << "" << "| ";
        cout << setw(22) << left << "Date/Time" << "| ";
        cout << setw(25) << left << "S.Account Number" << "| ";
        cout << setw(15) << left << "R.Account Number" << "| ";
        cout << setw(12) << left << "Amount" << "| ";
        cout << setw(12) << left << "S.Balance" << "| ";
        cout << setw(12) << left << "R.Balance" << "| ";
        cout << setw(12) << left << "User";

        cout << "\n" << setw(8) << left << ""
            << "\n\t________________________________________________________________"
            << "____________________________________________________________________\n\n";


        if (vTransfers.empty())
            cout << "\t\t\t\tNo Logs Available In the System!";
        else
            for (clsBankClient::stTransfer& transfer : vTransfers)
            {
                _printTransfersHistory(transfer);
                cout << "\n";
            }
        cout << setw(8) << left << ""
            << "\n\t________________________________________________________________"
            << "____________________________________________________________________\n\n";

    }
};