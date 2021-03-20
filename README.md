# CSC3022F_Assignment1
# Author: Ian Edwards, EDWIAN004
Tag sorting and storing C++ introductory assignment.

Program notes:

Place textfiles to be read in the directory of the driver file.

- driver.cpp is the driver program with a main method that has the code to call the sourcefile functions, and implements an infinite while-loop continuously presenting a menu to the user.

- processTag.cpp is the sourcefile with functions to read the contents of the tag file, print it out, write it out to a file and list a specified tag and its details.

- processTag.h is the header file that defines the functions and structures used.

Compile program with "make". Run program with "./tag.exe"

Choose operations from the list of options presented in program ("c", "r", "p", "w", "l", "q")

"c" : This option clears the menu and redisplays the menu.

"r" : Enter the filename to be read, including its file extension.

"p" : Will print out vector contents of read tag file.

"w" : Will ask for a file name to write to, and thereafter writes out to the indicated filename.

"l" : Lists the vector entry of the specified tag name.

"q" : Exits the program.


