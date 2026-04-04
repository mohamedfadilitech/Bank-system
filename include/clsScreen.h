#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
    static void _drawScreenHeader(string title, string subTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;
        if (subTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        cout << "\n\t\t\t\t\t -User: " << currentUser.getFirstName() + " " + currentUser.getLastName() << "\n"; 
        cout << "\t\t\t\t\t -Date:";
        clsDate().print();
    }

    static bool checkAccessRights(clsUser::enPermissions permission)
    {
        if (!currentUser.checkAccessRights(permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  " << "Access Denied! Contact Your Admin \n";
            cout << "\t\t\t\t\t______________________________________ \n";
            return false;
        }
        return true;
    }

};