#include "file.hpp"

using namespace std;

// Standard constructor
file::file(string dirIn){
  directory = dirIn;

  string tempname = "";
  // Iterate through the directory, extract the name + the extension
  for (auto i = dirIn.cbegin(); i != dirIn.cend(); ++i){
    // If we reach a directory marker, reset the name
    if (*i == '/'){
      tempname = "";
    }
    else{
      tempname += *i;
    }
  }
  bool dot = false;
  ext = "";
  // Iterate through the extrated name + extension, and extract the extension
  for (auto i = tempname.cbegin(); i != tempname.cend(); ++i){
    if (dot){
      ext += *i;
    }
    if (*i == '.'){
      ext = "";
      dot = true;
    }
  }

  // Iterate backwards through the name + extension, extracting the name.
  for (auto i = tempname.cend(); i >= tempname.cbegin(); --i){
    if (*i == '.' || *i == '~'){
      name = "";
    }
    else{
      // Put each character at the back of the name (to effectively reverse it)
      name = *i + name;
    }
  }
}

// Is this file the source of the given file?
bool file::isSource(std::shared_ptr<file> fileIn){
  if (isName(fileIn)){
    for(auto fi = fileIn->directory.cbegin(); fi != fileIn->directory.cend(); ++fi){
      if ((*fi == '~') && *(fi+1) == '2' && *(fi+2) == '0'){
        return true;
      }
    }
  }
  return false;
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

string file::getName(){
  return name;
}

string file::getDirectory(){
  return directory;
}
