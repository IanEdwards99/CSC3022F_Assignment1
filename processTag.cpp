// processTag.cpp - implementation for tag processing

#include <iostream>
#include "processTag.h"
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}


std::vector<tagStruct> EDWIAN004::stackRead(std::string filename){
   std::stack<std::string> S;
   std::vector<tagStruct> vect;
   string line, chunk, tagName, tagText;
   bool found = false;

   ifstream ifs(filename.c_str());
   if (!ifs){cerr << "File open failed!" << endl;}
   else{
      while(getline(ifs, line)){
         istringstream iss(line);
         while (!iss.eof()){
            iss >> chunk;
            chunk = trim(chunk);

            while(chunk.length() > 0){
               if (chunk == "<")
                  break;
               else if (chunk[0] == '<' and chunk[1]!='/'){
                     tagName = chunk.substr(1, chunk.find(">", 0)-1);
                     chunk.erase(0, chunk.find(">", 0)+1);
                     S.push(tagName);

                     for (auto it = begin (vect); it != end (vect); ++it) {
                        if (it->tagname == tagName and tagName != ""){
                           found = true;
                           it->nrPairs += 1;
                           it->tagText = rtrim(it->tagText);
                           it->tagText += ":";
                           break;
                        }
                     }
                     if (!found){ vect.push_back(tagStruct{tagName, 1, ""} );}
                     found = false;
               }
               else if(chunk[0] == '<' and chunk[1] == '/'){
                  S.pop(); if (!S.empty()) tagName = S.top();
                  chunk.erase(0, chunk.find('>', 0)+1);
               }
               else if (chunk[0]!= '<'){ //if it is just text, process text.
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

void EDWIAN004::displayVect(std::vector<tagStruct> vect){
   for (auto it = begin (vect); it != end (vect); ++it) {
      cout << it->tagname<< ", ";
      cout << it->nrPairs << ", ";
      cout << it-> tagText << endl;
   }
}

void EDWIAN004::writeFile(std::vector<tagStruct> vect, std::string filename){
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

void EDWIAN004::outputTag(std::vector<tagStruct> vect, std::string tagName){
   for (auto it = begin (vect); it != end (vect); ++it) {
      if (it->tagname == tagName){
         cout << it->tagname<< ", ";
         cout << it->nrPairs << ", ";
         cout << it-> tagText << endl;
         break;
      }
   }
}