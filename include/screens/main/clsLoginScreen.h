#pragma once
#include <iostream>
#include "core/clsScreen.h"
#include "models/clsUser.h"
#include "core/Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static bool _login();

public:
    static bool showLoginScreen();
};