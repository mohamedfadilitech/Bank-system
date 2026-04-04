#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static bool _login();

public:
    static bool showLoginScreen();
};