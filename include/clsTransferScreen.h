#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "Global.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _print(clsBankClient& client) {

        cout << "\n\n Client Info: \n";
        cout << "==========================\n";
        cout << "\nAccount Number: " << client.getAccountNumber();
        cout << "\nClient Name: " << client.getFirstName() + " " + client.getLastName();
        cout << "\nAccount Balance: " << client.getAccountBalance();
        cout << "\n==========================\n";
    }

    static string _readAccountNumber(const string str)
    {
        string accountNumber = "";
        do
        {
            cout << str ;
            cin >> accountNumber;

            if (accountNumber.empty())
                cout << "\nAccount number cannot be empty, try again.";

        } while (accountNumber.empty());

        return accountNumber;
    }

public :

    //Accout to Transform from 
    static clsBankClient findSender()
    {
        string senderAccountNumber = _readAccountNumber("\nPlease Enter Account Number to Transfer From: ");

        while (!clsBankClient::isClientExist(senderAccountNumber))
        {
            cout << "\nClient with [" << senderAccountNumber << "] does not exist.\n";
            senderAccountNumber = _readAccountNumber("\nPlease Enter Account Number to Transfer From: ");
        }

        clsBankClient sender = clsBankClient::find(senderAccountNumber); // find the client using the account number and return it as a client object
        _print(sender);

        return sender;
    }

    //find reciever

    static clsBankClient findReciever() {
     
        string recieverAccountNumber = _readAccountNumber("\n Please Enter Account Number to Transfer To: ");

        while (!clsBankClient::isClientExist(recieverAccountNumber))
        {
            cout << "\nClient with [" << recieverAccountNumber << "] does not exist.\n";
            recieverAccountNumber = _readAccountNumber("\nPlease Enter Account Number to Transfer To: ");
        }
        clsBankClient  reciever = clsBankClient::find(recieverAccountNumber); // find the client using the account number and return it as a client object
        _print(reciever);
        return  reciever;
    }

    static void showTransferScreen() {

        char confirmation;
        _drawScreenHeader("\t   Transfer Screen");
        clsBankClient sender = findSender();
        clsBankClient reciever = findReciever();

        while(reciever.getAccountNumber() == sender.getAccountNumber())
        {
            system("cls");
            _drawScreenHeader("\t   Transfer Screen");
            cout << "\nCannot transfer to the same account.\n";
            sender = findSender();
            reciever = findReciever();
        }
        double amount = 0;
        amount = clsInputValidate::readDoubleNumberBetween("\nPlease enter the transfer amount : ", 0.01, sender.getAccountBalance());

        do {
            confirmation = clsInputValidate::readChar("Do Wanna Really Preform This Operation. Y | N : ");
        } while (confirmation != 'y' && confirmation != 'n');

        if (confirmation == 'y')
        {
            sender.withdraw(amount);
            reciever.deposit(amount);
            clsBankClient::loadTransferDataToFile(currentUser, sender, reciever, amount);
            cout << "\nOperation was done successfully.\n";
            _print(sender);
            _print(reciever);
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};

