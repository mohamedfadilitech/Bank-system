#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsCurrency.h"
#include "core/clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

    static double _readRate()
    {
        double newRate = 0;
        newRate = clsInputValidate::readDoubleNumber("\nEnter New Rate: ");
        return newRate;
    }

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
public:

    static void showUpdateCurrencyRateScreen()
    {
        _drawScreenHeader("\tUpdate Currency Screen");

        string currencyCode = "";
        currencyCode = clsInputValidate::readString("\nPlease Enter Currency Code: ");

        while (!clsCurrency::isCurrencyExist(currencyCode))
        {
            currencyCode = clsInputValidate::readString("\nCurrency is not found, choose another one: ");
        }

        clsCurrency currency = clsCurrency::findByCode(currencyCode);
        _printCurrency(currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            currency.updateRate(_readRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _printCurrency(currency);
        }
    }

};