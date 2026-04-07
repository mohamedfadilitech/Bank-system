#pragma once

#include<iostream>
#include<string>
#include "core/clsString.h"
#include <vector>
#include <fstream>

class clsCurrency
{

private:

    enum enMode { emptyMode = 0, updateMode = 1 };
    enMode _mode;

    string _country;
    string _currencyCode;
    string _currencyName;
    double _rate;

    static clsCurrency _convertLineToCurrencyObject(string line, string separator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = clsString::split(line, separator);

        return clsCurrency(enMode::updateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
            stod(vCurrencyData[3]));
    }

    static string _convertCurrencyObjectToLine(clsCurrency currency, string separator = "#//#")
    {
        string currencyRecord = "";
        currencyRecord += currency.getCountry() + separator;
        currencyRecord += currency.getCurrencyCode() + separator;
        currencyRecord += currency.getCurrencyName() + separator;
        currencyRecord += to_string(currency.getRate());

        return currencyRecord;
    }

    static vector<clsCurrency> _loadCurrenciesDataFromFile()
    {
        vector<clsCurrency> vCurrencies;

        fstream myFile;
        myFile.open("data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                clsCurrency currency = _convertLineToCurrencyObject(line);
                vCurrencies.push_back(currency);
            }
            myFile.close();
        }

        return vCurrencies;
    }
    

    static void _saveCurrencyDataToFile(vector<clsCurrency> vCurrencies)
    {
        fstream myFile;
        myFile.open("data/Currencies.txt", ios::out);

        string dataLine;

        if (myFile.is_open())
        {
            for (clsCurrency c : vCurrencies)
            {
                dataLine = _convertCurrencyObjectToLine(c);
                myFile << dataLine << endl;
            }
            myFile.close();
        }
    }

    void _update()
    {
        vector<clsCurrency> vCurrencies;
        vCurrencies = _loadCurrenciesDataFromFile();

        for (clsCurrency& c : vCurrencies)
        {
            if (c.getCurrencyCode() == getCurrencyCode())
            {
                c = *this;
                break;
            }
        }
        _saveCurrencyDataToFile(vCurrencies);
    }

    static clsCurrency _getEmptyCurrencyObject()
    {
        return clsCurrency(enMode::emptyMode, "", "", "", 0);
    }

public:

    clsCurrency(enMode mode, string country, string currencyCode, string currencyName, double rate)
    {
        _mode = mode;
        _country = country;
        _currencyCode = currencyCode;
        _currencyName = currencyName;
        _rate = rate;
    }

    static vector<clsCurrency> getAllUSDRates()
    {
        return _loadCurrenciesDataFromFile();
    }

    bool isEmpty()
    {
        return (_mode == enMode::emptyMode);
    }

    string getCountry()
    {
        return _country;
    }

    string getCurrencyCode()
    {
        return _currencyCode;
    }

    string getCurrencyName()
    {
        return _currencyName;
    }

    double getRate()
    {
        return _rate;
    }

    void updateRate(double newRate)
    {
        _rate = newRate;
        _update();
    }

    static clsCurrency findByCode(string currencyCode)
    {
        currencyCode = clsString::upperCase(currencyCode);

        fstream myFile;
        myFile.open("data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                clsCurrency currency = _convertLineToCurrencyObject(line);
                if (currency.getCurrencyCode() == currencyCode)
                {
                    myFile.close();
                    return currency;
                }
            }
            myFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static clsCurrency findByCountry(string country)
    {
        country = clsString::upperCase(country);

        fstream myFile;
        myFile.open("data/Currencies.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                clsCurrency currency = _convertLineToCurrencyObject(line);
                if (clsString::upperCase(currency.getCountry()) == country)
                {
                    myFile.close();
                    return currency;
                }
            }
            myFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static bool isCurrencyExist(string currencyCode)
    {
        clsCurrency c = clsCurrency::findByCode(currencyCode);
        return (!c.isEmpty());
    }

    static vector<clsCurrency> getCurrenciesList()
    {
        return _loadCurrenciesDataFromFile();
    }

    //calculate currencies

    static double exchangeToUsd(double sourceCurrency, double amount) {
        return amount / double(sourceCurrency);
    }

    static double calculateCurrencies(const string codeFrom, const string codeTo, double amount) {

        clsCurrency cCodeFrom = findByCode(codeFrom);
        clsCurrency cCodeTo = findByCode(codeTo);
        return exchangeToUsd(cCodeFrom.getRate(), amount) * double(cCodeTo.getRate());
    }
};