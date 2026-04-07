#pragma once
#include "models/clsBankClient.h"
#include "core/clsScreen.h"
class clsFindClientScreen : protected clsScreen {
private :
	static void _printClientInfo(clsBankClient& client)
	{
		cout << "\n\n Client Info: \n";
		cout << "==========================\n";
		cout << "\nAccount Number : " << client.getAccountNumber();
		cout << "\nClient Name    : " << client.getFirstName() + " " + client.getLastName();
		cout << "\nEmail          : " << client.getEmail();
		cout << "\nPhone          : " << client.getPhone();
		cout << "\nPin Code       : " << client.getPinCode();
		cout << "\nAccount Balance: " << client.getAccountBalance();
		cout << "\n==========================\n";
	}

public:
	static void showFindClientScreen()
	{
		if (!checkAccessRights(clsUser::enPermissions::pFindClient))
			return;
		string accountNumber;
		string title = "\t Find Client Screen";
		_drawScreenHeader(title);
		accountNumber = clsInputValidate::readString("Please enter the account number: ");
		while (!clsBankClient::isClientExist(accountNumber))
			accountNumber = clsInputValidate::readString("Account Number Not Found Please Enter A Valid One : ");
		clsBankClient client = clsBankClient::find(accountNumber);
		if (client.isEmpty())
		{
			cout << "\nClient Not Found\n";
			return ;
		}
		cout << "\nClient Found Successfully :-)\n";
		_printClientInfo(client);
	}
};
