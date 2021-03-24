//Author: Ian Edwards - EDWIAN004
// processTag.cpp - implementation for tag processing. The sourcefile.

#include <iostream>
#include "processTag.h"
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

//space variable and ltrim, rtrim and trim are extra methods to trim off any unwanted characters from a string.
const std::string space = " \n\r\t\f\v";
 
std::string ltrim(const std::string& mystring)
{size_t start = mystring.find_first_not_of(space);return (start == std::string::npos)?"":mystring.substr(start);}
 
std::string rtrim(const std::string& mystring)
{size_t end = mystring.find_last_not_of(space);return (end == std::string::npos) ? "" : mystring.substr(0, end + 1);}
//trim calls both ltrim and rtrim to trim both sides of a string.
std::string trim(const std::string& mystring)
{return rtrim(ltrim(mystring));}

//sourcefile read function that accepts a filename and returns a populated vector depending on tags found within the file.
std::vector<tagStruct> EDWIAN004::stackRead(std::string filename){
   std::stack<std::string> S;       //stack name
   std::vector<tagStruct> vect;     //vector name
   string line, chunk, tagName, tagText;
   bool found = false;

   ifstream ifs(filename.c_str());     //load in file with a filestream
   if (!ifs){cerr << "File open failed!" << endl;} //check if file exists
   else{
      while(getline(ifs, line)){    //while file has more lines to read continue reading...
         istringstream iss(line);   //use a string stream to read in the line chunk by chunk separated by spaces.
         while (!iss.eof()){
            iss >> chunk;
            chunk = trim(chunk);

            while(chunk.length() > 0){ //whilst the chunk is not finished processing...
               if (chunk == "<") //check for invalid tag openings.
                  break;
               else if (chunk[0] == '<' and chunk[1]!='/'){ //if a tag is found, process the tag.
                     tagName = chunk.substr(1, chunk.find(">", 0)-1);
                     chunk.erase(0, chunk.find(">", 0)+1);
                     S.push(tagName);

                     for (auto it = begin (vect); it != end (vect); ++it) { //if tag is already in the vector, update it.
                        if (it->tagname == tagName and tagName != ""){
                           found = true;
                           it->nrPairs += 1;
                           it->tagText = rtrim(it->tagText);
                           it->tagText += ":";
                           break;
                        }
                     }
                     if (!found){ vect.push_back(tagStruct{tagName, 1, ""} );} //if tag is not in the vector, add it inside a new structure.
                     found = false;
               }
               else if(chunk[0] == '<' and chunk[1] == '/'){ //if the closing tag is found, remove the active tag from the stack and erase the chunk.
                  S.pop(); if (!S.empty()) tagName = S.top();
                  chunk.erase(0, chunk.find('>', 0)+1);
               }
               else if (chunk[0]!= '<'){ //if it is just text, process text one character at a time according to the active tag found ontop of the stack.
                  for (auto it = begin (vect); it != end (vect); ++it) {
                     tagName = S.top();
                     if (it->tagname == tagName and tagName != ""){
                        if (chunk.length()==1){
                           it->tagText += chunk[0];
                           it->tagText += ' ';
                        }
                        else it->tagText += chunk[0];
                        chunk.erase(0, 1);
                        break;
                     }
                  }
               }
            }
         }
      }
      ifs.close();
      cout << "File read successfully." << endl;
   }
   return vect;
}

void EDWIAN004::displayVect(std::vector<tagStruct> vect){ //Function to display the contents of the vector inputted.
   for (auto it = begin (vect); it != end (vect); ++it) {
      cout << it->tagname<< ", ";
      cout << it->nrPairs << ", ";
      cout << it-> tagText << endl;
   }
}

void EDWIAN004::writeFile(std::vector<tagStruct> vect, std::string filename){ //function to output the contents of a vector to a specified file.
   ofstream myFile;
   myFile.open(filename.c_str());
   for (auto it = begin (vect); it != end (vect); ++it) {
      myFile << it->tagname<< ", ";
      myFile << it->nrPairs << ", ";
      myFile << it-> tagText << endl;
   }
   myFile.close();
   cout << "File written successfully." << endl;
}

void EDWIAN004::outputTag(std::vector<tagStruct> vect, std::string tagName){ //Find in the inputted vector the specified tag name and output its values.
   for (auto it = begin (vect); it != end (vect); ++it) {
      if (it->tagname == tagName){
         cout << it->tagname<< ", ";
         cout << it->nrPairs << ", ";
         cout << it-> tagText << endl;
         break;
      }
   }
}