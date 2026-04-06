#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
   
    enMode _mode;
    string _userName;
    string _password;
    int _permissions;
    bool _markedForDelete = false;


    
    
    static clsUser _convertLinetoUserObject(string line, string seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::split(line, seperator);

        return clsUser(enMode::updateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

    }


    static string _converUserObjectToLine(clsUser &user, string seperator = "#//#")
    {
        string userRecord = "";
        string encryptedpassWd = user.getPassword();
        clsUtil::encryptText(encryptedpassWd, 5);

        userRecord += user.getFirstName() + seperator;
        userRecord += user.getLastName() + seperator;
        userRecord += user.getEmail() + seperator;
        userRecord += user.getPhone() + seperator;
        userRecord += user.getUserName() + seperator;
        userRecord += encryptedpassWd + seperator;
        userRecord += to_string(user.getPermissions());

        return userRecord;
    }
  
    static string _convertUserLoginDataToLine(clsUser &currentUser, string separator = "#//#") {
        string loginData = "";
        clsDate d;
        loginData += to_string(d.getDay()) + "/" +
            to_string(d.getMonth()) + "/" +
            to_string(d.getYear()) + "__" +
            to_string(d.getHours()) + ":" +
            to_string(d.getMinutes()) + ":" +
            to_string(d.getSeconds()) + separator;

        loginData += currentUser.getUserName() + separator;
        loginData += to_string(currentUser.getPermissions());
        return loginData;
    }

    static vector <clsUser> _loadUsersDataFromFile()
    {
        vector <clsUser> vUsers;

        fstream myFile;
        myFile.open("data/Users.txt", ios::in);//read Mode

        if (myFile.is_open())
        {
            string line;
            
            while (getline(myFile, line))
            {
                clsUser user = _convertLinetoUserObject(line);
                vUsers.push_back(user);
            }
            myFile.close();
        }
        return vUsers;
    }


    static void _saveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream myFile;
        myFile.open("data/Users.txt", ios::out);//overwrite

        string dataLine;

        if (myFile.is_open())
        {

            for (clsUser u : vUsers)
            {
                if (u.markedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.

                    dataLine = _converUserObjectToLine(u);
                    myFile << dataLine << endl;

                }
            }
            myFile.close();
        }
    }

    void _update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (clsUser& u : _vUsers)
        {
			if (u.getUserName() == getUserName()) //we will update the record that has the same user name as current object
            {
				u = *this; //update the record with current object data
                break;
            }

        }
        _saveUsersDataToFile(_vUsers);
    }

    void _addNew()
    {
		_addDataLineToFile(_converUserObjectToLine(*this)); //we will add new record to file by converting current object to line and then add it to file
    }

    void _addDataLineToFile(string stDataLine)
    {
        fstream myFile;
        myFile.open("data/Users.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            myFile << stDataLine << "\n";
            myFile.close();
        }

    }

public:
	//Permissions
	enum enPermissions {pAll = -1 , pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64 , PLogHistory = 128 };
    struct stLoginHistory {
        string date;
        string userName;
        int permission;
    };
    clsUser(enMode mode, string firstName, string lastName,
        string email, string phone, string userName, string password,
        int permissions) :
        clsPerson(firstName, lastName, email, phone)

    {
        _mode = mode;
        _userName = userName;
        _password = password;
        _permissions = permissions;
    }

	static clsUser getEmptyUserObject() //we will use this function to return empty user object when we want to return empty user object from find function if user not found, and also we will use it to set current user to empty user object after logout.
    {
        return clsUser(enMode::emptyMode, "", "", "", "", "", "", 0);
    }
    bool isEmpty()
    {
        return (_mode == enMode::emptyMode);
    }

    bool markedForDeleted()
    {
        return _markedForDelete;
    }

    string getUserName()
    {
        return _userName;
    }

    void setUserName(string userName)
    {
        _userName = userName;
    }

    void setPassword(string password)
    {
        _password = password;
    }

    string getPassword()
    {
        return _password;
    }

    void setPermissions(int permissions)
    {
        _permissions = permissions;
    }

    int getPermissions()
    {
        return _permissions;
    }

    static clsUser find(string userName)
    {
        fstream myFile;
        myFile.open("data/Users.txt", ios::in);//read Mode


        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                clsUser user = _convertLinetoUserObject(line);
                if (user.getUserName() == userName)
                {
                    myFile.close();
                    return user;
                }
            }
            myFile.close();
        }

        return getEmptyUserObject();
    }

    static clsUser find(string userName, string password)
    {

        fstream myFile;
        myFile.open("data/Users.txt", ios::in);//read Mode

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                if (line.empty())
                    break;
                clsUser user = _convertLinetoUserObject(line);
                string decryptedPasswd = user.getPassword();
                clsUtil::decryptText(decryptedPasswd, 5);
                if (user.getUserName() == userName && decryptedPasswd== password)
                {
                    myFile.close();
                    return user;
                }
            }
            myFile.close();
        }
        return getEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults save()
    {
        switch (_mode)
        {
        case enMode::emptyMode:
            return enSaveResults::svFaildEmptyObject; 

        case enMode::updateMode:
            _update();
            return enSaveResults::svSucceeded;

        case enMode::addNewMode:
            if (clsUser::isUserExist(_userName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _addNew();
                _mode = enMode::updateMode;
                return enSaveResults::svSucceeded;
            }

        default:
            return enSaveResults::svFaildEmptyObject; 
        }
    }

    static bool isUserExist(string userName)
    {
        clsUser user = clsUser::find(userName);
        return (!user.isEmpty());
    }

    bool deleteUser()
    {
        vector <clsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (clsUser& u : _vUsers)
        {
            if (u.getUserName() == getUserName())
            {
                u._markedForDelete = true;
                break;
            }

        }

        _saveUsersDataToFile(_vUsers);

        *this = getEmptyUserObject();

        return true;

    }
    
    static clsUser getAddNewUserObject(string userName)
    {
        return clsUser(enMode::addNewMode, "", "", "", "", userName, "", 0);
    }

    static vector <clsUser> getUsersList()
    {
        return _loadUsersDataFromFile();
    }

  
    bool checkAccessRights(enPermissions permission)
    {
        if(this->getPermissions() == pAll)
			return true; // if the user has all permissions, we will return true without checking the required permission bit, because the user has all permissions.

        return (this->getPermissions() & permission) == permission; //we will check if the user has the required permission by using bitwise AND operator to check if the required permission bit is set in the user's permissions.
	}

    // helpers for history logs 
    static void loadLoginDataToFile(clsUser &currentUser)
    {
        fstream myFile;
        myFile.open("data/loginHistory.txt", ios::app);
        if (myFile.is_open())
        {
            myFile << _convertUserLoginDataToLine(currentUser) << "\n";
            myFile.close();
        }
    }

    // for history file 
    static  stLoginHistory convertLinetoSt(string line, string seperator = "#//#") {
        vector<string> vLogsData;
        stLoginHistory logs;

        vLogsData = clsString::split(line, seperator);

        logs.date = vLogsData[0];
        logs.userName = vLogsData[1];
        logs.permission = stoi(vLogsData[2]);

        return logs;
    }

    static vector<stLoginHistory> loadLoginsHistory() {
        vector<stLoginHistory> vLogs;

        fstream myFile;
        myFile.open("data/loginHistory.txt", ios::in);//read Mode

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                if (line.empty())
                    continue;
                stLoginHistory log = convertLinetoSt(line);
                vLogs.push_back(log);
            }
            myFile.close();
        }
        return vLogs;
    }
 

    static vector<stLoginHistory> getLogsList() {
        return loadLoginsHistory();
    }
    
};