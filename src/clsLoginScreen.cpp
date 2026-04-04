#include "../include/clsLoginScreen.h"
#include "../include/clsMainScreen.h"

bool clsLoginScreen::_login()
{
    bool loginFailed = false;
    string username, password;
    short attempts = 3; 

    do
    {
        if (loginFailed)
        {
            attempts--;

            if (attempts == 0)
            {
                cout << "\nYou Are Locked After 3 Failed Attempts\n";
                return false;
            }

            cout << "\nInvalid Username/Password!\n\n";
            cout << attempts << " Attempts Left\n";
        }

        cout << "Enter Username? ";
        cin >> username;

        cout << "Enter Password? ";
        cin >> password;

        currentUser = clsUser::find(username, password);
        loginFailed = currentUser.isEmpty();

    } while (loginFailed);
    clsUser::loadLoginDataToFile(currentUser);
    clsMainScreen::showMainMenu();
    return true;
}

bool clsLoginScreen::showLoginScreen()
{
	system("cls");
	_drawScreenHeader("\t  Login Screen");
	return _login();

}