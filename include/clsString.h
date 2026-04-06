#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{

private:
    string _Value;

public:

    clsString() { _Value = ""; }

    clsString(string Value) { _Value = Value; }

    void SetValue(string Value) { _Value = Value; }

    string GetValue() const { return _Value; }

    void    print() {
        cout << "####### " << GetValue() << " #######" << endl;
    }

    // count function with count function overloading

    static short CountWords(const string& S1) {
        if (S1.empty()) return 0;

        short counter = 0;
        bool  inWord = false;   

        for (char c : S1) {
            if (c != ' ' && !inWord) {
                inWord = true;
                counter++;
            }
            else if (c == ' ') {
               
                inWord = false;
            }
        }
        return counter;
    }

    short CountWords()
    {
        return CountWords(_Value);
    };
    //======================================================================================

    // countVowles function with count function overloading

   static size_t countVowels(const string& str) {
       size_t counter = 0;
       string vowels = "aeiouAEIOU";  // كل الـ vowels

       for (char c : str) {
           if (vowels.find(c) != string::npos)
               counter++;
       }
       return counter;
   }
    size_t  countVowels() {
       return countVowels(GetValue());
    }
    //======================================================================================
    // split function with split function overloading
         
    static vector<string> split(string str, const string& delim) {
        string sWord;
        size_t pos = 0;
        vector<string> vStr;

        while ((pos = str.find(delim)) != string::npos) {
            sWord = str.substr(0, pos);
            if (sWord != "") vStr.push_back(sWord);
            str = str.erase(0, pos + delim.length());
        }
       sWord = str.substr(0);
       if (sWord != "") vStr.push_back(sWord);
        return vStr;
    }

    vector<string> split(const string& delim) {
        return split(GetValue(), delim);
    }
    //======================================================================================

    // join function

    static string join(const vector<string>& vStr, const string& delim) {
        string str = "";
        for (size_t i = 0; i < vStr.size(); i++) {
            if (i != 0) str += delim;
            str += vStr[i];
        }
        return str;
    }
    //======================================================================================

     // lowerCase function with lowerCase function overloading
        
    static string lowerCase(const string& str) {
        string s;

        for (const char& c : str) s += tolower(c);
        return s;
    }

    string lowerCase() {
    return lowerCase(GetValue());
    }
    //======================================================================================
    // upperCase function with upperCase function overloading

    static string upperCase(const string& str) {
        string s;

        for (const char& c : str) s += toupper(c);
        return s;
    }

    string upperCase() {
      return upperCase(GetValue());
    }
    //======================================================================================
    // upperCaseFirstletter function with upperCaseFirstletter function overloading

    static string upperCaseFirstletter(const string& str) {
        string s;
        s = (char)toupper(str[0]);
        for (size_t i = 1; i < str.length(); i++) 
            s += (char)tolower(str[i]);
        return s;
    }
    string upperCaseFirstletter() {
        return upperCaseFirstletter(GetValue());
    }
    //======================================================================================
    // countCapitals function with countCapitals function overloading

    static bool   is_capital(const char c) { return (c >= 'A' && c <= 'Z'); }

     static size_t countCapitals(const string& str) {
        size_t counter = 0;
        for (const char c : str) {if(is_capital(c)) counter++;}
        return counter;
    }
     size_t countCapitals() {
         return countCapitals(GetValue());
     }
    //======================================================================================
     // replaceWord function with replaceWord function overloading
    static  string replaceWord(string str, const string word, const string wordToReplace) {
         if (str == "")
             return "";
         vector<string> vStr = split(str, " ");
         for (string &s : vStr) {
             if (s == word)
                 s = wordToReplace;
         }
         return str = join(vStr, " ");
     }
    string replaceWord(string word, string wordToReplace) {

        return replaceWord(GetValue(), word, wordToReplace);
    }
     //======================================================================================

};


