#include <iostream>
#include "../include/screens/main/clsLoginScreen.h"
#include "../include/models/clsUser.h"
#include "../include/core/Global.h"


using namespace std;

clsUser currentUser = clsUser::getEmptyUserObject(); // We will use this global variable to store the currently logged-in user data, and we will set it to empty user object when there is no logged-in user, and we will update it with the logged-in user data when the user logs in successfully.
int main() {
	
	if (!clsLoginScreen::showLoginScreen()) 
		return 0;
	
}