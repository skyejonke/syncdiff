#include "parser.hpp"

using namespace std;

parser::parser(){
  system("find . -maxdepth 20 -type f > /tmp/ls.txt");
  ifstream ifile = ifstream("/tmp/ls.txt");

  string line;


  if(!ifile){
    cout << "Nothing found" << endl;
    /* Setup exceptions here */
  }
  else {
    while(getline(ifile, line)) {
      if (line.substr(0,13) == "./.stversions") {
        confFiles.push_back(shared_ptr<conflictFile> (new conflictFile(line)));
        line = "";
      }
      else {
        files.push_back(shared_ptr<file> (new file((line))));
        line = "";
      }
    }
  }
  setSources();
}

unique_ptr<vector<string>> parser::getNames(){
  unique_ptr<vector<string>> output (new vector<string>);
  for (auto it = files.begin(); it != files.end(); ++it){
    shared_ptr<file> temp = *it;
    output->push_back(temp->getName().append(" || ").append(temp->getDirectory()));
  }
  for (auto it = confFiles.begin(); it != confFiles.end(); ++it){
    shared_ptr<file> temp = *it;
    output->push_back(temp->getName().append(" || ").append(temp->getDirectory()));
  }
  return output;
}


void parser::setSources(){
  for (auto itf = files.begin(); itf != files.end(); ++itf){
    for (auto itc = confFiles.begin(); itc != confFiles.end(); ++itc){
      shared_ptr<file> tempFile = *itf;
      shared_ptr<conflictFile> tempConf = *itc;
      if (tempFile->isName(tempConf)){
        cout << tempConf->getName();
        tempConf->setSource(tempFile);
      }
    }
  }
}

void parser::compareAll(){
  for (auto f : confFiles){
    if (f != NULL){
      /* cout << "-----" << endl; */
      /* cout << f->getName() << f->getDirectory() << endl; */
      f->compare();
    }
  }
}

