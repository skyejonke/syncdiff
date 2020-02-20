#include "file.hpp"

using namespace std;

file::file(string dirIn){
  directory = dirIn;
}

bool file::isSource(string pathIn){
  /* auto fi; */
  int namelen = 0;
  for (auto pi = pathIn.cend(); pi != pathIn.cbegin(); --pi){
    if (to_string(*pi) == "/"){
      break;
    }
    namelen++;
  }
  namelen = pathIn.size() - namelen;
  auto ni = name.begin();
  ni++;
  int i = 0;
  for(auto pi = pathIn.cbegin(); pi != pathIn.cend() && ni != name.cend(); ++pi){
    if (i > namelen){

      if (*pi != *ni){
        if (to_string(*pi) == "~" || to_string(*pi) == "2" || to_string(*pi) == "0"){
          cout << "stuff";

        }
      }
      ++ni;
    }
  }
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



int main() {
  parser par = parser();
  /* file test = file("test.txt"); */
  /* vector<string> t = test.getContents(); */

  /* shared_ptr<file> ptr (new file("test.txt")); */

  /* shared_ptr<conflictFile> cTest( */
  /*     new conflictFile("test2.txt",ptr)); */

  /* auto ints = cTest->compare(); */

  /* if (ints->size() != 0){ */
  /*   bool done = false; */

  /*   cout << "Keep? (l/r, 1/2)" << endl; */
  /*   string in; */
  /*   cin >> in; */

  /*   while (!done){ */
  /*     if (in == "l" || in == "1"){ */
  /*       done = true; */
  /*     } */
  /*     else if (in == "r" || in == "2"){ */
  /*       done = true; */
  /*       test.setContents(cTest); */
  /*     } */
  /*     else { */
  /*       cout << "Please input again." << endl; */
  /*       cin >> in; */
  /*     } */
  /*   } */
  /* } */


  return 0;
}

