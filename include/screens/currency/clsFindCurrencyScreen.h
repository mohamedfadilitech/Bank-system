#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsCurrency.h"
#include "core/clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _printCurrency(clsCurrency &currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << currency.getCountry();
        cout << "\nCode       : " << currency.getCurrencyCode();
        cout << "\nName       : " << currency.getCurrencyName();
        cout << "\nRate(1$) = : " << currency.getRate();
        cout << "\n_____________________________\n";
    }

    static void _showResults(clsCurrency &currency)
    {
        if (!currency.isEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _printCurrency(currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void showFindCurrencyScreen()
    {
        _drawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short answer = 1;
        cin >> answer;

        if (answer == 1)
        {
            string currencyCode;
            currencyCode = clsInputValidate::readString("\nPlease Enter Currency Code : ");
            clsCurrency currency = clsCurrency::findByCode(currencyCode);
            _showResults(currency);
        }
        else
        {
            string country;
            country = clsInputValidate::readString("\nPlease Enter Country Name: ");
            clsCurrency currency = clsCurrency::findByCountry(country);
            _showResults(currency);
        }
    }

};