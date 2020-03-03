#include "conflictfile.hpp"

using namespace std;

conflictFile::conflictFile(string dirIn): file(dirIn){
  source = nullptr;
}

bool conflictFile::setSource(shared_ptr<file> fileIn){
  if (fileIn != nullptr){
    source = fileIn;
    return true;
  }
  return false;
}

// Compare the conflict file and it's source, and return the lines that are
// different.
unique_ptr<vector<int>> conflictFile::compare(){
  unsigned long linesize = 70;
  //cout << source << endl;
  unique_ptr<vector<int>> ints(new vector<int>);

  if (source != nullptr){
    //cout << source->getDirectory() << endl;
    auto sour = source->getContents();
    auto conf = this->getContents();
    string sourline = "";
    string confline = "";

    unsigned long len = (sour.size() >= conf.size())
      ? sour.size() : conf.size();

    string sep;
    for (unsigned long j = 0; j < linesize*2; j++){
      sep += "-";
    }
    //cout << sep << endl;


    for (unsigned long i = 0; i < len; i++){
      sourline = "";
      confline = "";
      if (i < sour.size()) {
        sourline += sour.at(i);
      }
      if (i < conf.size()){
        confline += conf.at(i);
      }

      if (confline != sourline){
        ints->push_back(i);
        "--" + sourline;
        confline += "--";
      }
      else{
        sourline = "  " + sourline; }
      while (sourline.length() < linesize - 3){
        sourline += " ";
      }

      sourline += "|";

      while (confline.length() < linesize - 3){
        confline += " ";
      }

      //cout << to_string(i) << sourline << to_string(i) << "  " << confline << endl;

    }

    sep = "";
    for (unsigned long j = 0; j < linesize*2; j++){
      sep += "-";
    }
    //cout << sep << endl;
  }
  return ints;
}

shared_ptr<file> conflictFile::getSource(){
  return source;
}

shared_ptr<file> conflictFile::makeSource(){
  cout << "started makesource" << endl;
  if (source == nullptr){
    cout << "Found NULL" << endl;
    string nDir = "";
    cout << getDirectory() << endl;
    string dir = getDirectory();
    bool withinVersions = false;
    for (auto it = dir.cbegin(); it != dir.cend(); ++it){
      cout <<  *(it+5) << endl;

      if ((
            *it == '.'
            && *(it+1) == 's'
            && *(it+2) == 't'
            && *(it+3) == 'v')
          || (
            *it == '~'
            && *(it+1) == '2'
            && *(it+2) == '0')
         ){
        withinVersions = true;
      }

      if (!withinVersions){
        nDir += *it;
      }

      if (*it == '/'){
        withinVersions = false;
      }


    }
    cout << nDir << endl;
    source = shared_ptr<file> (new file(nDir));
  }
    return source;
}

