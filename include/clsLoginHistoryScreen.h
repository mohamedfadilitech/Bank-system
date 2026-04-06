#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsLoginHistoryScreen : protected clsScreen
{
private:
    static void _printLoginHistory(clsUser::stLoginHistory logs)
    {
        cout << setw(8) << left << "" << "| " << setw(22) << left << logs.date;
        cout << "| " << setw(25) << left << logs.userName;
        cout << "| " << setw(12) << left << logs.permission;
    }

public:

    static void showLogList()
    {
        if (!checkAccessRights(clsUser::PLogHistory))
            return ;
        vector <clsUser::stLoginHistory> vLogs = clsUser::getLogsList();

        string title = "\t  Users History Logs";
        string subTitle = "\t    (" + to_string(vLogs.size()) + ") Log(s).";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(22) << "Date/Time";
        cout << "| " << left << setw(25) << "Username";
        cout << "| " << left << setw(12) << "Permissions";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Logs Available In the System!";
        else
            for (clsUser::stLoginHistory log : vLogs)
            {
                _printLoginHistory(log);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};
