#include "file.hpp"

using namespace std;

file::file(string dirIn){
  directory = dirIn;

  string tempname = "";
  for (auto i = dirIn.cbegin(); i != dirIn.cend(); ++i){
    if (*i == '/'){
      tempname = "";
    }
    else{
      tempname += *i;
    }
  }
  bool dot = false;
  ext = "";
  for (auto i = tempname.cbegin(); i != tempname.cend(); ++i){
    if (dot){
      ext += *i;
    }
    if (*i == '.'){
      ext = "";
      dot = true;
    }
  }
}

bool file::isSource(std::shared_ptr<file> fileIn){
  /* auto fi; */

  auto ni = name.begin();
  ni++;
  int i = 0;
  for(auto fi = fileIn->directory.cbegin(); fi != fileIn->directory.cend() && fi != name.cend(); ++fi){
    if (i > directory.size()){

      if (*fi != *ni){
        if (to_string(*fi) == "~" || to_string(*fi) == "2" || to_string(*fi) == "0"){
          cout << "stuff";

        }
      }
      ++ni;
    }
  }
}

// Check if the two files refer to the same file
bool file::isName(shared_ptr<file> fileIn){
  return(fileIn->name == name && fileIn->ext == ext);

}

vector<string> file::getContents() {
  ifstream ifile;
  ifile.open(directory);
  vector<string> out;
  if(!ifile){
    cout << "Nothing found" << endl;
    /* Setup exceptions here */
  } else {
    string line;
    while(getline(ifile, line)) {
      out.push_back(line);
    }
  }
  ifile.close();
  return out;
}

bool file::setContents(shared_ptr<file> fileIn){
  vector<string> toWrite = fileIn->getContents();
  ofstream ofile(directory);
  for (auto i : toWrite){
    ofile << i << "\n";
  }
  return true;
}





