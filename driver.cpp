#include <iostream>   //a system header file - needed to do simple I/O
#include "processTag.h"	         // our header file - contains decl of fib()
#include <string>
#include <cstdlib>

// struct tagStruct {
//    std::string tagname;
//    int nrPairs;
//    std::string tagText;
// };

int main (void)
{
	using namespace std;  
	vector<tagStruct> vect;

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
			std::cout << "Enter a filename..." << std::endl;
			string file;
			std::cin >> file;
			vect = EDWIAN004::stackRead(file);
		}
		else if (input == "p"){
			std::cout << "Printing..." << std::endl;
			EDWIAN004::displayVect(vect);
		}
		else if (input == "d"){
			std::cout << "Enter filename to write to:" << std::endl;
			std::cin >> input;
			EDWIAN004::writeFile(vect, input);
		}
		else if (input == "l") {
			std::cout << "Enter a tag name to output:" << std::endl;
			std::string tagName;
			std::cin >> tagName;
			EDWIAN004::outputTag(vect, tagName);
		}

		cout << "c: Clear display.\nr: Read and process tag file\np: Print all tags\nd: Write tags\nl: List tags\nq: Quit\n\nEnter an option (r,p,d,l) or q to quit, and press return..." << std::endl;
		cin >>input;
	}
	std::cout << "Program exited." << std::endl;
	return 0; // always return a value to calling system

}
