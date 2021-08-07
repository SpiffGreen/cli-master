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
string trimLeft(string);
string trimRight(string str);
string trim(string str);


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

string trimLeft(string str) {
    int i;
    for(i = 0; i < str.size(); i++) {
        if(str[i] != ' ') break;
    }
    return str.substr(i);
}

string trimRight(string str) {
    int i;
    for(i = str.size() - 1; i >= 0; i--) {
        if(str[i] != ' ') break;
    }
    return str.substr(0, i + 1);
}

string trim(string str) {
    return trimLeft(trimRight(str));
}

#endif