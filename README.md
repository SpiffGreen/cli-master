## Cli-Master

A command line utility library that simplifies the development of command line apps. Made for flexibility and simplicity.

### Installation
Simply download and place the Cli_Master.h file in the c++ compiler include directory or in your project folder
The file can be gotten [Here](./Cli_Master.h).

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
* Boolean based flags will have a value of `'true'`

### License
Cli-Master is [MIT](./LICENSE) licensed