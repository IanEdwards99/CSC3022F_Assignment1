// processTag.cpp - implementation for tag processing

#include <iostream>
#include <string>
#include "processTag.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

struct tagStruct {
   std::string tagname;
   int nrPairs;
   std::string tagText;
};

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


void EDWIAN004::stackRead(std::string filename){
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
            cout << "My chunk: " + chunk << endl;

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
                           cout << "struct: " + tagName + ", " << it->nrPairs << + ", " + tagText << endl;
                           break;
                        }
                     }
                     if (!found){ vect.push_back(tagStruct{tagName, 1, ""} );
                        cout << "struct: " + tagName + ", " << 1 << endl;}
                     found = false;
               }
               else if(chunk[0] == '<' and chunk[1] == '/'){
                  cout << "Erasing closing tag..." << endl;
                  S.pop(); if (!S.empty()) tagName = S.top();
                  chunk.erase(0, chunk.find('>', 0)+1);
                  cout << "Success!" << endl;
                  // if (line.length() < 2) line.erase(0, 2);
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
                        cout << "added: " << it->tagText << " chunk: " + chunk << endl; 
                        break;
                     }
                  }
               }
            }
         }
      }
      ifs.close();
      for (auto it = begin (vect); it != end (vect); ++it) {
         it->tagText = rtrim(it->tagText);
         cout << it->tagname << ", " << it->tagText << ", " << it->nrPairs << endl;
      }
   }
}


void EDWIAN004::readFile(std::string filename)
{
   vector<tagStruct> vect;
   bool finishedTagName = false;
   bool finishedTagText = false;
   bool found = false;
   string line;
   string tagName = "";
   string tagText = "";

   ifstream ifs(filename.c_str());
   if (!ifs){cerr << "File open failed!" << endl;}
   else {
      while (getline(ifs, line)){
         line = trim(line);
         cout << "line: " + line << endl;
         while (line.length() != 0){
            if (!finishedTagName){
               if (line[0] == '<' and line[1] != '/'){ //find an extract tag.
                  tagName = line.substr(1, line.find(">", 0)-1);
                  line.erase(0, line.find(">", 0)+1);
                  finishedTagName = true;
                  cout << "tagname: " + tagName << endl;
                  cout << "line: " + line << endl;
               }
               else if (line[0] == '<' and line[1] == '/'){
                  line.erase(0, line.find('>', 0)+1);
                  if (line.length() < 2) line.erase(0, 2);}
            }
            if (finishedTagName and !finishedTagText){
               if (line[0] == '<' and line[1] == '/'){ //if we reach the closing tag.
                  finishedTagText = true;
                  //now search vector and update or push to vector.

                  for (auto it = begin (vect); it != end (vect); ++it) {
                     if (it->tagname == tagName and tagName != ""){
                        found = true;
                        it->nrPairs += 1;
                        it->tagText += ":" + tagText;
                        cout << "struct: " + tagName + ", " << it->nrPairs << + ", " + tagText << endl;
                        break;
                     }
                  }
                  if (!found){ vect.push_back(tagStruct{tagName, 1, tagText} );
                     cout << "struct: " + tagName + ", " << 1 << + ", " + tagText << endl;}
                  finishedTagName = false;
                  finishedTagText = false;
                  found = false;
                  tagName = "";
                  tagText = "";
                  line.erase(0, line.find('>', 0)+1);
                  if (line.length() < 2) line.erase(0, 2);
                  cout << "erased line after closing tag: " + line << line.length() << endl;
               }
               else if (line[0] != '<'){
                  tagText += line[0];
                  line.erase(0, 1);
                  cout << "line: " + line << endl;
                  cout << "tagText: " + tagText << endl;
               }
            }
         }
      }
      ifs.close();
      for (auto it = begin (vect); it != end (vect); ++it) {
         cout << it - vect.begin() << ", ";
         cout << it->tagname<< ", ";
         cout << it->nrPairs << ", ";
         cout << it-> tagText << endl;
      }


      // while (ifs.getline(line,100)){
      //    cout << "Next line is: " << line << endl;

      //    std::istringstream iss(line);//grab chunk of line.
      //    string value, token; //store a chunk of the input stream.
      //    bool status;

      //    while (getline(iss, token, '<')){ //each line starts with tag now.
      //       cout << "chunk: " + token << endl;
      //       if (token[0] != '/'){
      //          tagName = token.substr(0, token.find(">", 0)); //From the start we will always encounter a tagName first.
      //          cout << "tagName: " + tagName << endl;
      //          if (tagName != "") finishedTagName = true;
      //          if (finishedTagName){
      //             token.erase(0, token.find(">", 0)+1); //remove tagName from chunk. Whats left is some of the tag text, might have more next line.
      //             cout << "erase 1: " + token << endl;
      //             if (token.length() != 0){
      //                tagText += token; //multiple lines??
      //                // finishedTagText = true;
      //             }

      //             // if (std::find(vect.begin(), vect.end(), ))
      //             if (finishedTagText){
      //                for (auto it = begin (vect); it != end (vect); ++it) {
      //                   if (it->tagname == tagName and tagName != ""){
      //                      found = true;
      //                      it->nrPairs += 1;
      //                      it->tagText += ":" + tagText;
      //                      cout << "struct: " + tagName + " ," << it->nrPairs << + " ," + tagText << endl;
      //                   }
      //                }
      //                if (!found){ vect.push_back(tagStruct{tagName, 1, tagText}); 
      //                   cout << "struct: " + tagName + " ," + tagText << endl;}
      //             }
      //          }
      //          if (finishedTagName and finishedTagText){
      //             finishedTagName = false;
      //             finishedTagText = false;
      //          }
      //       }
      //       else { //if reach closing tag, erase it.
      //          token.erase(0, token.find(">", 0)+1);
      //          cout << "erase 2: " + token << endl;
      //       }
      //    } //cout << "tagname:" + tagName << endl; cout << "tagText:" + tagText << endl;
      // }
      // ifs.close();
      // for (auto it = begin (vect); it != end (vect); ++it) {
      //    cout << it - vect.begin() << ", ";
      //    cout << it->tagname<< ", ";
      //    cout << it->nrPairs << ", ";
      //    cout << it-> tagText << endl;
      // }
   }
   
}

// void EDWIAN004::createStruct(char line[100]){ //single line is passed into this function, which will create the structure from it, after filtering the data out.
//    istringstream iss(line);
//    string value; //store a chunk of the input stream.
//    while (!iss.eof()){
//       iss >> value;
//       for (int i = 0; i < value.length(); i++){

//       }
//       // cout << value << endl;
//    }


            // if (finishedTagName){
            //    if (line[i] == '<'){
            //       finishedTagName = false;
            //       continue;
            //    }
            //    else tagText += line[i];
            // }
            // else if (finishedTagName != true and finishedTagText){
            //    if (line[i] == '>')
            //       finishedTagName = true;
            //    else
            //       tagName += line[i];
            // }