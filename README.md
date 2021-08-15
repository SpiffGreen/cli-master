## Cli-Master

A command line utility library that simplifies the development of command line apps. Made for flexibility and simplicity.

### Installation
Simply download and place the Cli_Master.h file in the c++ compiler include directory or in your project folder
The file can be gotten [Here](./climaster.h).

### Development
This project was tested with a MinGW C++ compiler. Included in this repository is a build and run [script](./build_and_run.sh) to ease development process.

`How to use the build script`
* Simple run the script but pass the name of the file without extension.
```sh
# source file name -> main.cpp
$ ./build_and_run.sh main
```
This will generate a main.exe file and run it. If an error occurs during the compile process the executable won't run.

### Documentation
Cli-Master provides a class with some useful functions.
* `description`  This function sets the description for your program. It accepts only one parameter: ```string```
* `version` This method like the description method sets the version of your program
* `option` This method is dedicated to adding flags your command-line program will accept. It accepts three parameters all ```string```:
    * `Flag` - format `"<short>, <long>"`. Example:
    `"-l, --length"`
    * `Description` - A simple description of the purpose of a flag
    * `defaultValue` - A default value for a flag
* `parse` This method accepts two parameters: the `no. of arguments` passed to your program from `main(int argc, char** argv)`, a pointer to the arguments. This will form the values needed by your application.
* `opts` This method takes no parameters and simply returns a `map<string, string>` of flags and their values.

### Notes
* Opts will return an empty map if parse is not called before it.
* Boolean based flags will have a value of `'true'` in the opts map.

### Example
A simple command line program that expect two kinds of cli options `firstname` and `lastname`. If any other option is used the help menu is printed.
```c++
#include "Cli_Master.h"
#include <map>
using namespace std;
int main(int argc, char** argv) {
    Cli_Master program;
    program.description("This is the first version of the Cli_Master C++ library for building command line apps");
    program.version("v1.0.0");
    program.option("-f, --firstname", "your first name", "John");
    program.option("-l, --lastname", "your last name", "Doe");
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
```

### Author
[Spiff Jekey-Green](https://github.com/SpiffGreen)

### License
Cli-Master is [MIT](./LICENSE) licensed