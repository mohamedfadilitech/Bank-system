#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsCurrency.h"
#include "core/clsString.h"
#include "core/clsInputValidate.h"
#include <iomanip>

class clsCurrencyCalculatorScreen : public clsScreen {

private:
     static void _printExchangeResultUI(const string & codeFrom,const string & codeTo, double amount,double result) {
             cout << "\n";
             cout << "+=======================================+\n";
             cout << "|         CURRENCY EXCHANGE RESULT      |\n";
             cout << "+=======================================+\n";

             cout << "| " << left << setw(15) << "From"
                 << ": " << setw(18) << codeFrom << "|\n";

             cout << "| " << left << setw(15) << "To"
                 << ": " << setw(18) << codeTo << "|\n";

             cout << "| " << left << setw(15) << "Amount"
                 << ": " << setw(18) << amount << "|\n";

             cout << "| " << left << setw(15) << "Result"
                 << ": " << setw(18) << result << "|\n";

             cout << "+=======================================+\n";
         }
      
public:
    static void showCurrencyExchangeCalculator() {
        string currencyCode_1 = "";
        string currencyCode_2 = ""; 
        double amount;

        do {
            system("cls");
            _drawScreenHeader("\tCurrency Exchange Calculator");
            currencyCode_1 = clsInputValidate::readString("\nPlease Enter Currency1 Code: ");

            while (!clsCurrency::isCurrencyExist(currencyCode_1))
            {
                currencyCode_1 = clsInputValidate::readString("\nCurrency is not found, choose another one: ");
            }
            currencyCode_2 = clsInputValidate::readString("\nPlease Enter Currency2 Code: ");
            while (!clsCurrency::isCurrencyExist(currencyCode_2))
            {
                currencyCode_2 = clsInputValidate::readString("\nCurrency is not found, choose another one: ");
            }
            amount = clsInputValidate::readDoubleNumberBetween("\nEnter The Amount You Wanna Exchange : ", 0, 1000000);

           double exchangeResult = clsCurrency::calculateCurrencies(currencyCode_1, currencyCode_2, amount);
           _printExchangeResultUI(currencyCode_1, currencyCode_2, amount, exchangeResult);
          
        } while (clsInputValidate::readChar("\nDo You Want to Perform This Operation again : Y | N ") == 'y');
    }
};