/**
 * @package Cli-Master - A command line utility library that simplifies the development of command line apps
 * @author  Spiff Jekey-Green
 * @license MIT
 */

#ifndef CLI_MASTER_H
#define CLI_MASTER_H

#include "util.h"
#include <map>
#include <vector>
#include <iterator>

#define CLI_MASTER_DEFAULT_OPTION "Options:"
#define CLI_MASTER_DEFAULT_EMPTY ""

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
    this->helpVector.assign({
        CLI_MASTER_DEFAULT_EMPTY, 
        CLI_MASTER_DEFAULT_EMPTY, 
        CLI_MASTER_DEFAULT_OPTION
        });
    this->setDescription("A sample program"); // Set a default description
    this->option("-h, --help", "shows this help menu", "false"); // set a default help value
    this->version("0.0.0"); // set a default version
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
    this->helpVector[0] = this->programDescription;
}

void Cli_Master::version(string version = " ") {
    this->programVersion = version;
    this->option("-V, --version", "output the version number", version);
}

void Cli_Master::option(string flag, string description, string defaultValue) {
    vector<string>::iterator itr = this->helpVector.begin();
    advance(itr, 3);
    this->helpVector.insert(itr, flag + "\t" + description);
    int commaIndex = flag.find(",");
    if(commaIndex == -1) throw "Flag should contain a comma seperated list of short and long version";
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
        string argument = argv[i];
        // string argument = *(argv + i);
        int index = argument.find("=");
        if(index == -1) {
            /** No support for boolean based values yet */
            if(startsWith(argument, "--")) {
                // perform operation for long flags
                string key = trim(argument, '-');
                try {
                    map<string, string>::iterator m = this->programLongOptions.find(key);
                    this->parsedFlags.insert(pair<string, string> (m->first, "true"));
                } catch(const std::exception& e) {
                    this->printHelp();
                    return;
                }
            } else if(startsWith(argument, "-")) {
                // perform operation for short flags
                string key = trim(argument, '-');
                try {
                    map<string, string>::iterator m = this->programShortOptions.find(key);
                    this->parsedFlags.insert(pair<string, string> (m->first, "true"));
                    // println("This is a short key " + key); // For debugging
                }
                catch(const std::exception& e) {
                    this->printHelp();
                    return;
                }
            } else {
                this->printHelp();
                return;
            }
        } else {
            string key = argument.substr(0, index);
            string value = argument.substr(index + 1);
            if(startsWith(key, "--")) {
                // This means its a long flag
                key = trim(key, '-');
                try {
                    map<string, string>::iterator m = this->programLongOptions.find(key);
                    this->parsedFlags.insert(pair<string, string> (m->first, value));
                }
                catch(const std::exception& e) {
                    this->printHelp();
                    return;
                }
            } else if(startsWith(key, "-")) {
                // perform operation for short flag
                key = trim(key, '-');
                try {
                    map<string, string>::iterator m = this->programShortOptions.find(key);
                    this->parsedFlags.insert(pair<string, string> (m->first, value));
                }
                catch(const std::exception& e) {
                    this->printHelp();
                    return;
                }
            } else {
                this->printHelp();
                return;
            }
        }
    }
    return;
}

map<string, string> Cli_Master::opts() {
    return this->parsedFlags;
}

#endif