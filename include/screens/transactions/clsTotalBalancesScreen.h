#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsBankClient.h"
#include <iomanip>
#include "core/clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:

    static void _printClientRecordBalanceLine(clsBankClient client)
    {
        cout << setw(25) << left << ""
            << "| " << setw(15) << left << client.getAccountNumber();

        cout << "| " << setw(40) << left << client.getFirstName() + " " + client.getLastName();

        cout << "| " << setw(12) << left << client.getAccountBalance();
    }

public:

    static void showTotalBalancesScreen()
    {
        vector<clsBankClient> clients = clsBankClient::getClientsList();

        string title = "\t  Balances List Screen";
        string subTitle = "\t    (" + to_string(clients.size()) + ") Client(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(25) << left << ""<< "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << ""
            << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";

        cout << setw(25) << left << ""
            << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double totalBalances = clsBankClient::getTotalBalances();

        if (clients.empty())
        {
            cout << "\t\t\t\tNo clients available in the system!";
        }
        else
        {
            for (clsBankClient client : clients)
            {
                _printClientRecordBalanceLine(client);
                cout << endl;
            }
        }

        cout << setw(25) << left << ""
            << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(8) << left << ""
            << "\t\t\t\t\t\t\t     Total Balances = "
            << totalBalances << endl;

        cout << setw(8) << left << ""
            << "\t\t\t\t  ( "
            << clsUtil::digitsToString(totalBalances)
            << ")";
    }
};