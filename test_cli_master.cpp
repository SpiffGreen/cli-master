/**
 * A simple application to test the use of Cli_Master library
 */

#include "Cli_Master.h"

int main(int argc, char** argv) {
    Cli_Master passgen;
    passgen.description("This is the first version of the Cli_Master C++ library for building command line apps");
    passgen.version("v1.0.0");
    passgen.option("-l, --length", "length of password", "8");
    passgen.parse(argc, argv);
    auto m = passgen.opts();
    map<string, string>::iterator itr;
    for(itr = m.begin(); itr != m.end(); itr++) {
        println("Key: " + itr->first + ", Value: " + itr->second);
    }
    return 0;
}