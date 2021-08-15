#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

// using namespace std;

// Declarations
template <typename T>
void print(T);

template <typename T>
void println(T);

std::string input(std::string);
std::string trimLeft(std::string, char, int);
std::string trimRight(std::string, char, int);
std::string trim(std::string, char, int);
bool startsWith(std::string, std::string);


// Definitions
template <typename T>
void print(T x) {
    std::cout << x;
}

template <typename T>
void println(T x) {
    std::cout << x << std::endl;
}

std::string input(std::string question) {
    print(question);
    std::string answer;
    getline(std::cin, answer);
    return answer;
}

std::string trimLeft(std::string str, char delimeter = ' ', int depth = 0) {
    int i;
    for(i = 0; i < str.size(); i++) {
        if(str[i] != delimeter) break;
        if(depth != 0) {
            if(i >= depth) break;
        }
    }
    return str.substr(i);
}

std::string trimRight(std::string str, char delimeter = ' ', int depth = 0) {
    int i;
    bool defaultDepth = false;
    if(depth == 0) defaultDepth = true;
    for(i = str.size() - 1; i >= 0; i--) {
        if(str[i] != delimeter) break;
        if(depth != 0) depth--;
        else {
            if(!defaultDepth) break;
        }
    }
    return str.substr(0, i + 1);
}

std::string trim(std::string str, char delimeter = ' ', int depth = 0) {
    return trimLeft(trimRight(str, delimeter, depth), delimeter, depth);
}

bool startsWith(std::string str, std::string ch) {
    int index = str.find(ch);
    return (index == 0) ? true : false;
}

#endif