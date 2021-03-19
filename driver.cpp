#include <iostream>   //a system header file - needed to do simple I/O
#include "processTag.h"	         // our header file - contains decl of fib()
#include <string>
#include <cstdlib>

int main (void)
{
	using namespace std;  

	cout << "c: Clear display.\nr: Read and process tag file\np: Print all tags\nd: Write tags\nl: List tags\nq: Quit\n\nEnter an option (r,p,d,l) or q to quit, and press return..." << std::endl;
	string input;
	cin >> input; //can also use input = cin.get(); reads next character.
	
	string name = "my little pony";
	for (int i = 0; i <= 10; i++){
		cout << name[i];
	}

	while (input != "q") {
		if (input == "c"){system("clear");}
		else if (input == "r"){
			std::cout << "Enter a filename...\n" << std::endl;
			string file;
			std::cin >> file;
			EDWIAN004::stackRead(file);
		}
		else if (input == "p"){std::cout << "Printing...\n" << std::endl;}
		else if (input == "d"){std::cout << "Writing...\n" << std::endl;}
		else if (input == "l") {std::cout << "Listing...\n" << std::endl;}

		cout << "c: Clear display.\nr: Read and process tag file\np: Print all tags\nd: Write tags\nl: List tags\nq: Quit\n\nEnter an option (r,p,d,l) or q to quit, and press return..." << std::endl;
		cin >>input;
	}
	std::cout << "Program exited." << std::endl;
	return 0; // always return a value to calling system

}
