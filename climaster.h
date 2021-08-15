/**
 * @package CliMaster - A command line utility library that simplifies the development of command line apps
 * @author  Spiff Jekey-Green
 * @license MIT
 */

#ifndef CLIMASTER_H
#define CLIMASTER_H

#include "util.h"
#include <map>
#include <vector>
#include <iterator>

#define CLI_MASTER_DEFAULT_OPTION "Options:"
#define CLI_MASTER_DEFAULT_EMPTY ""

class CliMaster {
    protected:
        std::string programVersion;
        std::string programDescription;
        std::vector<std::string> helpVector;
        std::map<std::string, std::string> programShortOptions;
        std::map<std::string, std::string> programLongOptions;
        std::map<std::string, std::string> parsedFlags;

        // protected methods
        void printHelp();
        void setDescription(std::string);

    public:
        CliMaster();
        virtual ~CliMaster() = default;
        
        // operational methods
        void parse(int, char**);
        void option(std::string, std::string, std::string);
        std::map<std::string, std::string> opts(); // return a map of option with their values gotten after the parse function was called.
        void version(std::string);
        void description(std::string);
};

CliMaster::CliMaster() {
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

void CliMaster::printHelp() {
    for(auto item: this->helpVector) {
        println(item);
    }
}

void CliMaster::description(std::string desc = " ") {
    this->programDescription = desc;
    this->helpVector.at(0) = desc;
}

void CliMaster::setDescription(std::string desc = " ") {
    this->programDescription = desc;
    this->helpVector[0] = this->programDescription;
}

void CliMaster::version(std::string version = " ") {
    this->programVersion = version;
    this->option("-V, --version", "output the version number", version);
}

void CliMaster::option(std::string flag, std::string description, std::string defaultValue) {
    std::vector<std::string>::iterator itr = this->helpVector.begin();
    advance(itr, 3);
    this->helpVector.insert(itr, flag + "\t" + description);
    int commaIndex = flag.find(",");
    if(commaIndex == -1) throw "Flag should contain a comma seperated list of short and long version";
    std::string shortStr = flag.substr(0, commaIndex);
    std::string longStr = flag.substr(commaIndex + 1);
    longStr = trim(longStr);
    shortStr = trim(shortStr);
    this->programShortOptions.insert(std::pair<std::string, std::string> (trim(shortStr, '-'), defaultValue));
    this->programLongOptions.insert(std::pair<std::string, std::string> (trim(longStr, '-'), defaultValue));
}

void CliMaster::parse(int argc, char** argv) {
    if(argc < 2) {
        this->printHelp();
        return;
    }
    // perform main logic here
    for(int i = 1; i < argc; i++) {
        std::string argument = argv[i];
        // string argument = *(argv + i);
        int index = argument.find("=");
        if(index == -1) {
            /** No support for boolean based values yet */
            if(startsWith(argument, "--")) {
                // perform operation for long flags
                std::string key = trim(argument, '-');
                std::map<std::string, std::string>::iterator m = this->programLongOptions.find(key);
                if(m != this->programLongOptions.end()) {
                    this->parsedFlags.insert(std::pair<std::string, std::string> (m->first, "true"));
                } else {
                    this->printHelp();
                    return;
                }
            } else if(startsWith(argument, "-")) {
                // perform operation for short flags
                std::string key = trim(argument, '-');
                std::map<std::string, std::string>::iterator m = this->programShortOptions.find(key);
                if(m != this->programShortOptions.end()) {
                    this->parsedFlags.insert(std::pair<std::string, std::string> (m->first, "true"));
                } else {
                    this->printHelp();
                    return;
                }
            } else {
                this->printHelp();
                return;
            }
        } else {
            std::string key = argument.substr(0, index);
            std::string value = argument.substr(index + 1);
            if(startsWith(key, "--")) {
                // This means its a long flag
                key = trim(key, '-');
                std::map<std::string, std::string>::iterator m = this->programLongOptions.find(key);
                if(m != this->programLongOptions.end()) {
                    this->parsedFlags.insert(std::pair<std::string, std::string> (m->first, value));
                } else {
                    this->printHelp();
                    return;
                }
            } else if(startsWith(key, "-")) {
                // perform operation for short flag
                key = trim(key, '-');
                std::map<std::string, std::string>::iterator m = this->programShortOptions.find(key);
                if(m != this->programShortOptions.end()) {
                    this->parsedFlags.insert(std::pair<std::string, std::string> (m->first, value));
                } else {
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

std::map<std::string, std::string> CliMaster::opts() {
    return this->parsedFlags;
}

#endif