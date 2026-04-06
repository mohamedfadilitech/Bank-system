#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen
{

private:
    static void _printCurrencyRecordLine(clsCurrency &currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << currency.getCountry();
        cout << "| " << setw(8) << left << currency.getCurrencyCode();
        cout << "| " << setw(45) << left << currency.getCurrencyName();
        cout << "| " << setw(10) << left << currency.getRate();
    }

public:

    static void showCurrenciesListScreen()
    {
        vector<clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();
        string title = "\t  Currencies List Screen";
        string subTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

        _drawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else
            for (clsCurrency currency : vCurrencies)
            {
                _printCurrencyRecordLine(currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;
    }

};