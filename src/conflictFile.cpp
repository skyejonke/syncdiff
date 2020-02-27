#include "conflictfile.hpp"

using namespace std;

conflictFile::conflictFile(string dirIn): file(dirIn){
  source = NULL;
}

bool conflictFile::setSource(shared_ptr<file> fileIn){
  source = fileIn;
  return true;
}


shared_ptr<vector<int>> conflictFile::compare(){
  int linesize = 70;
  auto sour = source->getContents();
  auto conf = this->getContents();
  string sourline = "";
  string confline = "";

  shared_ptr<vector<int>> ints(new vector<int>);

  int len = (sour.size() >= conf.size())
    ? sour.size() : conf.size();

  string sep;
  for (int j = 0; j < linesize*2; j++){
    sep += "-";
  }
  cout << sep << endl;


  for (int i = 0; i < len; i++){
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
      sourline = "  " + sourline;
    }

    while (sourline.length() < linesize - 3){
      sourline += " ";
    }

    sourline += "|";

    while (confline.length() < linesize - 3){
      confline += " ";
    }

    cout << to_string(i) << sourline << to_string(i) << "  " << confline << endl;

  }

  sep = "";
  for (int j = 0; j < linesize*2; j++){
    sep += "-";
  }
  cout << sep << endl;
  return ints;

}
