#ifndef _tag
#define _tag

struct tagStruct {
   std::string tagname;
   int nrPairs;
   std::string tagText;
};

#include <vector>

namespace EDWIAN004 {
void readFile(std::string filename);

void createStruct(char line[100]);

std::vector<tagStruct> stackRead(std::string filename);

void displayVect(std::vector<tagStruct> vect);

void writeFile(std::vector<tagStruct> vect, std::string filename);

void outputTag(std::vector<tagStruct> vect, std::string tagName);

#endif
}
