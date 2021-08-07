#ifndef CLI_MASTER_H
#define CLI_MASTER_H

#include "util.h"
#include <map>
#include <vector>
#include <iterator>

class Cli_Master {
    protected:
        string programVersion;
        string programDescription;
        vector<string> helpVector;
        map<string, string> programShortOptions;
        map<string, string> programLongOptions;
        map<string, string> parsedFlags;

        // protected methods
        void printHelp();
        void setDescription(string);

    public:
        Cli_Master();
        virtual ~Cli_Master() = default;
        
        // operational methods
        void parse(int, char**);
        void option(string, string, string);
        map<string, string> opts(); // return a map of option with their values gotten after the parse function was called.
        void version(string);
        void description(string);
};

Cli_Master::Cli_Master() {
    this->helpVector.clear(); // Clear all elements in the helpVector if any
    this->setDescription("A sample program"); // Set a default description
    this->version("0.0.0"); // set a default version
    this->helpVector.assign({
        this->programDescription, 
        "", 
        "Options:",
        "-V, --version\toutput the version number",
        "-h, --help\tshows this help menu"
        });
};

void Cli_Master::printHelp() {
    for(auto item: this->helpVector) {
        println(item);
    }
}

void Cli_Master::description(string desc = " ") {
    this->programDescription = desc;
    this->helpVector.at(0) = desc;
}

void Cli_Master::setDescription(string desc = " ") {
    this->programDescription = desc;
}

void Cli_Master::version(string version = " ") {
    this->programVersion = version;
}

void Cli_Master::option(string flag, string description, string defaultValue) {
    vector<string>::iterator itr = this->helpVector.begin();
    advance(itr, 3);
    this->helpVector.insert(itr, flag + "\t" + description);
    int commaIndex = flag.find(",");
    if(commaIndex == -1) throw "Flag should contain a short and long version";
    string shortStr = flag.substr(0, commaIndex);
    string longStr = flag.substr(commaIndex + 1);
    longStr = trim(longStr);
    shortStr = trim(shortStr);
    this->programShortOptions.insert(pair<string, string> (trim(shortStr, '-'), defaultValue));
    this->programLongOptions.insert(pair<string, string> (trim(longStr, '-'), defaultValue));
}

void Cli_Master::parse(int argc, char** argv) {
    if(argc < 2) {
        this->printHelp();
        return;
    }
    // perform main logic here
    for(int i = 1; i < argc; i++) {
        string argument = *(argv + i);
        int index = argument.find("=");
        if(index == -1) {
            /** No support for boolean based values yet */
            // map<string, string>::iterator itr;
            // for(itr = this->programLongOptions.begin(); itr != this->programLongOptions.end(); itr++) {
            //     // println("Key: " + itr->first);
            //     // println("Value: " + itr->second);
            // }
        } else {
            string key = argument.substr(0, index);
            string value = argument.substr(index + 1);
            if(startsWith(key, "--")) {
                // This means its a long flag
                key = trim(key, '-');
                map<string, string>::iterator m = this->programLongOptions.find(key);
                // println(m->second); // Check if m exists before using it's value
            } else {
                // perform operation for short flag
            }
            this->parsedFlags.insert(pair<string, string> (trim(key, '-'), value));
        }
    }
}

map<string, string> Cli_Master::opts() {
    return this->parsedFlags;
}

#endif