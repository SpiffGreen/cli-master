#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

using namespace std;

// Declarations
template <typename T>
void print(T);

template <typename T>
void println(T);

string input(string);
string trimLeft(string, char);
string trimRight(string, char);
string trim(string, char);
bool startsWith(string, string);


// Definitions
template <typename T>
void print(T x) {
    cout << x;
}

template <typename T>
void println(T x) {
    cout << x << endl;
}

string input(string question) {
    print(question);
    string answer;
    getline(cin, answer);
    return answer;
}

string trimLeft(string str, char delimeter = ' ') {
    int i;
    for(i = 0; i < str.size(); i++) {
        if(str[i] != delimeter) break;
    }
    return str.substr(i);
}

string trimRight(string str, char delimeter = ' ') {
    int i;
    for(i = str.size() - 1; i >= 0; i--) {
        if(str[i] != delimeter) break;
    }
    return str.substr(0, i + 1);
}

string trim(string str, char delimeter = ' ') {
    return trimLeft(trimRight(str, delimeter), delimeter);
}

bool startsWith(string str, string ch) {
    int index = str.find(ch);
    return (index == 0) ? true : false;
}

#endif