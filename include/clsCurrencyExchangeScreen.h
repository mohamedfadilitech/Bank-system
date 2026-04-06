#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include <iomanip>

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{

private:
    enum enCurrenciesMainMenuOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4, eMainMenu = 5
    };

    static short _readCurrenciesMainMenuOptions()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short choice = clsInputValidate::readIntBetween("",1, 5);
        return choice;
    }

    static void _goBackToCurrenciesMenu()
    {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        system("pause>0");
        showCurrenciesMenu();
    }

    static void _showCurrenciesListScreen()
    {
        clsCurrenciesListScreen::showCurrenciesListScreen();
    }

    static void _showFindCurrencyScreen()
    {
        clsFindCurrencyScreen::showFindCurrencyScreen();
    }

    static void _showUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::showUpdateCurrencyRateScreen();
    }

    static void _showCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::showCurrencyExchangeCalculator();
    }

    static void _performCurrenciesMainMenuOptions(enCurrenciesMainMenuOptions currenciesMainMenuOptions)
    {
        switch (currenciesMainMenuOptions)
        {
        case enCurrenciesMainMenuOptions::eListCurrencies:
        {
            system("cls");
            _showCurrenciesListScreen();
            _goBackToCurrenciesMenu();
            break;
        }

        case enCurrenciesMainMenuOptions::eFindCurrency:
        {
            system("cls");
            _showFindCurrencyScreen();
            _goBackToCurrenciesMenu();
            break;
        }

        case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
        {
            system("cls");
            _showUpdateCurrencyRateScreen();
            _goBackToCurrenciesMenu();
            break;
        }

        case enCurrenciesMainMenuOptions::eCurrencyCalculator:
        {
            system("cls");
            _showCurrencyCalculatorScreen();
            _goBackToCurrenciesMenu();
            break;
        }

        case enCurrenciesMainMenuOptions::eMainMenu:
        {
            // do nothing here, the main screen will handle it :-)
        }
        }
    }

public:

    static void showCurrenciesMenu()
    {
        system("cls");
        _drawScreenHeader("    Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performCurrenciesMainMenuOptions((enCurrenciesMainMenuOptions)_readCurrenciesMainMenuOptions());
    }

};