#include "parser.hpp"

using namespace std;

parser::parser(string head){

  /* system(("cd " + head).c_str()); */
  system(("find " + head + " -maxdepth 20 -type f > /tmp/ls.txt").c_str());
  ifstream ifile = ifstream("/tmp/ls.txt");

  string line;


  if(!ifile){
    cout << "Nothing found" << endl;
    /* Setup exceptions here */
  }
  else {
    // Iterate through each of the lines in files, corresponding to all
    // of the files the command finds.
    while(getline(ifile, line)) {
      // If the file is in the stversions directory.
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
    shared_ptr<conflictFile> temp = *it;
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
        tempConf->setSource(tempFile);
      }
      else {
        tempConf->setSource(shared_ptr<file> (nullptr));
      }
    }
  }
  for (auto c : confFiles){
    if (c->getSource() == nullptr){
      cout << c->getName() << endl;
      c->makeSource();
    }
  }
}

vector<parser::filePair> parser::compareAll(){
  vector<filePair> out = vector<filePair>();
  int i = 0;
  for (auto f : confFiles){
    if (f != NULL && f->isConflict){
      filePair temp;
      temp.ints = *(f->compare());
      temp.conf = confFiles.at(i);
      temp.source = f->getSource();
      out.push_back(temp);
    }
    i++;
  }
  return out;
}

/* void parser::compareSpecific(shared_ptr<file> file1, shared_ptr<file> file2){ */

/* } */

