#include "parser.hpp"

using namespace std;

parser::parser(){
  system("find . -maxdepth 1 -type d > /tmp/lsd.txt");
  ifstream idir = ifstream("/tmp/lsd.txt");

  string dir;
  string line;
  while(getline(idir, dir)) {
    string cmd = "find " + dir + " -maxdepth 1 -type f > /tmp/ls.txt";
    system(cmd.c_str());
    ifstream ifile = ifstream("/tmp/ls.txt");


    if(!ifile){
      cout << "Nothing found" << endl;
      /* Setup exceptions here */
    }
    else {
      while(getline(ifile, line)) {
        if (line.substr(0,11) == ".stversions"){
          files.push_back(shared_ptr<file> (new conflictFile(dir.append(line))));
          line = "";
        }
        else{
          files.push_back(shared_ptr<file> (new file(dir.append(line))));
          line = "";
        }
      }
    }
    dir = "";
  }

}
