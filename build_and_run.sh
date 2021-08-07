#! /usr/bin/bash
g++ "$1.cpp" -o "$1.exe" && ./$1.exe --length=32 --numbers=true --symbols=true