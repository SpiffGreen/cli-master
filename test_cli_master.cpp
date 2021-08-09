/**
 * A simple application to test the use of Cli_Master library
 */

#include "Cli_Master.h"

int main(int argc, char** argv) {
    Cli_Master program;
    program.description("This is the first version of the Cli_Master C++ library for building command line apps");
    // program.version("v1.0.0");
    program.option("-f, --firstname", "your first name", "John");
    program.option("-l, --lastname", "your last name", "Doe");
    program.option("-a, --age", "to specify your age", "18");
    program.option("-g, --gender", "user's gender", "male");
    program.option("-S, --save", "save generated details to file, details.txt", "true");
    program.parse(argc, argv);
    auto m = program.opts(); // Returns a map of the arguments with values. This map is used by the commandline-application.
    if(!m.empty()) {
        map<string, string>::iterator itr;
        for(itr = m.begin(); itr != m.end(); itr++) {
            println("Key: " + itr->first + ", Value: " + itr->second);
        }
    }
    return 0;
}